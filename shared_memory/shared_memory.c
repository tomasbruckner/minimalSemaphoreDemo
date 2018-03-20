/**
*   Author: Tomas Bruckner
*   Date: 20.3.2018  
*   Description: 
*       Example of two processes sharing variables in C for Linux.
*
*		To run type in terminal:
*           make run
*
*       If you are getting SIGSEGV, try:
*           rm /dev/shm/sem.shared_memory
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <time.h>
#include <signal.h>

#define SEMAPHORE_NAME "/shared_memory"
#define UNLOCKED 1

void set_resources();
void do_stuff();
void clean_resources();

sem_t *semaphore = NULL;
int *sharedCounter = NULL;
int *notSharedCounter = NULL;
int sharedCounterId = 0;

int main()
{
    // prevent buffering of the output
    setbuf(stdout, NULL);

    set_resources();

    pid_t processPid = fork();

    if (processPid == 0) // child
    {
        // initialize random number generator for child
        srand(time(NULL) ^ (getpid() << 16));

        for (int i = 0; i < 5; i++)
        {
            int randomTime = random() % 1000 * 1000;

            do_stuff("Child: ");

            usleep(randomTime);
        }

        exit(EXIT_SUCCESS);
    }
    else if (processPid > 0) //parent
    {
        // initialize random number generator for parent
        srand(time(NULL) ^ (getpid() << 16));

        for (int i = 0; i < 5; i++)
        {
            int randomTime = random() % 500 * 1000;

            do_stuff("Parent:");

            usleep(randomTime);
        }
    }
    else // error
    {
        // handle error
    }

    // wait for the child to end
    waitpid(processPid, NULL, 0);

    clean_resources();

    return EXIT_SUCCESS;
}

void set_resources()
{
    if ((sharedCounterId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        // handle error
    }

    if ((sharedCounter = shmat(sharedCounterId, NULL, 0)) == NULL)
    {
        // handle error
    }

    if ((notSharedCounter = malloc(sizeof(int))) == NULL)
    {
        // handle error
    }

    *sharedCounter = 1;
    *notSharedCounter = 1;

    if ((semaphore = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0666, UNLOCKED)) == SEM_FAILED)
    {
        // handle error
    }
}

void do_stuff(char *processName)
{
    sem_wait(semaphore);
    printf("%s shared counter value: %02d / not shared counter value: %02d\n", processName, (*sharedCounter)++, (*notSharedCounter)++);
    sem_post(semaphore);
}

void clean_resources()
{
    free(notSharedCounter);
    shmctl(sharedCounterId, IPC_RMID, NULL);
    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);
}
