# Introduction to the concurrency programming in C
There are two simple examples of basic structures that should help student of [Brno University of Technology](https://www.fit.vutbr.cz/) with their project to the subject Operating Systems. I have created these examples because in my opinion it is sometimes unnecessary difficult to understand it from the documentation. Hopefully, it will make easier for students (but not only them) to grasp the basics of multi-process programming and corresponding data structures (semaphores).

I tried to make the examples as simple as possible with focus on what is important in the given example.

The repository contains two examples (it will not work on the Windows OS).

1. semaphore_synchronization
2. shared_memory

It is recommended to understand `semaphore_synchronization` before trying to understand `shared_memory`.

## Semaphore synchronization
You can run the program in the `semaphore_synchronization` folder using:

```
make run
```

This will output:

```
Child  process 1
Parent process 1
Child  process 2
Parent process 2
Child  process 3
Parent process 3
Child  process 4
Parent process 4
Child  process 5
Parent process 5
Waiting for child to end
Child ended
Parent ended
```

Notice that output is ordered and will be deterministic every time you run the program. This is secured by two semaphores (see source code).

## Shared memory
You can run the program in the `shared_memory` folder using:

```
make run
```

This will output:

```
Parent: shared counter value: 01 / not shared counter value: 01
Child:  shared counter value: 02 / not shared counter value: 01
Child:  shared counter value: 03 / not shared counter value: 02
Parent: shared counter value: 04 / not shared counter value: 02
Parent: shared counter value: 05 / not shared counter value: 03
Parent: shared counter value: 06 / not shared counter value: 04
Child:  shared counter value: 07 / not shared counter value: 03
Parent: shared counter value: 08 / not shared counter value: 05
Child:  shared counter value: 09 / not shared counter value: 04
Child:  shared counter value: 10 / not shared counter value: 05
```

Notice that output is not deterministic and can vary each time you run it. Only the `shared counter value` is ordered.


## SIGSEGV error
This is probably caused because you are trying to create 

 If you are getting SIGSEGV in `shared_memory` example, try:

```
rm /dev/shm/sem.shared_memory
```

If you are getting SIGSEGV in `semaphore_synchronization` example, try:

```
rm /dev/shm/sem.semaphore_synchronization1 /dev/shm/sem.semaphore_synchronization2
```

Ideally, you should prefix the names of the semaphores with your `xlogin` so it is ensured that it will be unique on shared Linux machines (Merlin, Eva).
