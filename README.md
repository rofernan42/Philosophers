# Philosophers
## Summary
The aim of this project is to learn the basics of threading a process and how to work on the same memory space, and learn how to use mutex, semaphores and shared memory.
## Rules
This project comes from the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* 
* 

## Compilation
```
make
```
## Execution
```
./philo_* arg1 arg2 arg3 arg4 [optionnal]arg5
```
Where:
* arg1 = number of philosophers.
* arg2 = time to die in milliseconds. If a philosopher doesn't start to eat after [arg2] ms after starting his last meal or the beginning of the simulation, he dies.
* arg3 = time to eat in ms. During that time, the philosopher will keep 2 forks.
* arg4 = time to sleep in ms.
* arg5 = number of time each philosopher must eat (optionnal). If specified, defines the number of meals all philosophers must at least eat; if not specified, the simulation stops at the death of a philosopher.
