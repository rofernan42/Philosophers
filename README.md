# Philosophers
## Summary
The aim of this project is to learn the basics of threading a process and how to work on the same memory space, and learn how to use mutex, semaphores and shared memory.
## Rules
This project comes from the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).
* there are forks on the table (as many forks as philosophers).
* the philosophers must never be starving.
* a philosopher needs 2 forks to eat.
* a philosopher must drop his forks and sleep after eating.
* a philosopher must think after sleeping.
* the philosophers don't speak with each other.
* a philosopher doesn't know if another philosopher is about to die.
* the simulation stops when a philosopher dies.
* we can't have more than 10 milliseconds between the death of a philosopher and the printing of his death.
## Philo_one
- Use of threads and mutex.
- One fork between each philosopher, each fork being represented by a mutex.
- One thread per philosopher.
## Philo_two
- Use of threads and semaphores.
- All the forks are in the middle of the table.
- The number of available forks is represented by a semaphore.
- One thread per philosopher.
## Philo_three
- Use of processes and semaphores.
- All the forks are in the middle of the table.
- The number of available forks is represented by a semaphore.
- One process per philosopher.
## Compilation
```
make
```
## Execution
```
./philo_* arg1 arg2 arg3 arg4 arg5(optionnal)
```
Where:
* arg1 = number of philosophers and forks.
* arg2 = time to die in milliseconds. If a philosopher doesn't start to eat after [arg2] ms after starting his last meal or the beginning of the simulation, he dies.
* arg3 = time to eat in ms. During that time, the philosopher will keep 2 forks.
* arg4 = time to sleep in ms.
* arg5 = number of time each philosopher must eat (optionnal). If specified, defines the number of meals all philosophers must at least eat and the simulation stops when it is done; if not specified, the simulation stops at the death of a philosopher.
