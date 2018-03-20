/**
*   Author: Tomas Bruckner
*   Date: 20.3.2018
*   Description: 
*       Example of two processes synchronized by two semaphores in C for Linux.
*
*		To run type in terminal:
*           make run
*
*       If you are getting SIGSEGV, try:
*           rm /dev/shm/sem.semaphore_synchronization1 /dev/shm/sem.semaphore_synchronization2
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>

#define SEMAPHORE1_NAME "/semaphore_synchronization1"
#define SEMAPHORE2_NAME "/semaphore_synchronization2"
#define LOCKED 0

sem_t *semaphore1 = NULL;
sem_t *semaphore2 = NULL;
int counter = 1;

int main()
{
    // prevent buffering of the output
    setbuf(stdout, NULL);

    // create two locked semaphores
    if ((semaphore1 = sem_open(SEMAPHORE1_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
    {
        // handle error
    }

    if ((semaphore2 = sem_open(SEMAPHORE2_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
    {
        // handle error
    }

    pid_t processPid = fork();

    if (processPid == 0) // child
    {
        for (int i = 0; i < 5; i++)
        {
            sem_wait(semaphore1);
            printf("Child  process %d\n", counter++);
            sem_post(semaphore2);
        }

        sem_wait(semaphore1);
        printf("Child ended\n");
        exit(EXIT_SUCCESS);
    }
    else if (processPid > 0) //parent
    {
        for (int i = 0; i < 5; i++)
        {
            sem_post(semaphore1);
            sem_wait(semaphore2);
            printf("Parent process %d\n", counter++);
        }
    }
    else // error
    {
        // handle error
    }

    printf("Waiting for child to end\n");
    sem_post(semaphore1);

    // wait for child to end
    waitpid(processPid, NULL, 0);

    printf("Parent ended\n");
    
    // close semaphores
    sem_close(semaphore1);
    sem_close(semaphore2);

    // remove semaphores
    sem_unlink(SEMAPHORE1_NAME);
    sem_unlink(SEMAPHORE2_NAME);

    return EXIT_SUCCESS;
}
