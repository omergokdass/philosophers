*This project has been created as part of the 42 curriculum by ogokdas.*

PHILOSOPHERS (PHILO)

DESCRIPTION
This project is an implementation of the classic Dining Philosophers problem using
threads and mutexes in C. Each philosopher is represented by a thread and each fork
is represented by a mutex. The purpose of the project is to manage shared resources
correctly, prevent data races, and ensure proper synchronization between threads.

Philosophers alternate between eating, sleeping, and thinking. If a philosopher
does not eat within the given time_to_die, the simulation stops and the philosopher
is declared dead.

INSTRUCTIONS

Compilation
make

Execution
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]

Examples
./philo 5 800 200 200
./philo 4 310 200 100
./philo 5 800 200 200 7

PROGRAM BEHAVIOR

Each philosopher runs in its own thread.

Forks are shared resources protected by mutexes.

Printing is protected to avoid mixed outputs.

A monitor thread checks for philosopher death.

An optional thread checks if all philosophers have eaten enough times.

FILE STRUCTURE

philo.c

Initializes philosophers and forks.

Creates philosopher threads and monitoring threads.

Contains the main philosopher routine (eat, sleep, think).

Handles the special case where there is only one philosopher.

thread.c

Contains the monitoring logic.

Checks if a philosopher has died due to starvation.

Checks if all philosophers have eaten the required number of times.

utils.c

Utility functions such as ft_atoi and argument parsing.

Time management functions (get_time, ms_sleep).

Thread-safe printing function.

main.c

Program entry point.

Waits for all threads using pthread_join.

Destroys mutexes and frees allocated memory before exit.

philo.h

Contains all structure definitions and function prototypes.

Defines philosopher and shared information structures.

TECHNICAL DETAILS

Uses POSIX threads (pthread).

Forks are implemented as mutexes.

Each philosopher has its own mutex to protect meal-related data.

Time is measured in milliseconds using gettimeofday.

RESOURCES
Dining Philosophers Problem
https://en.wikipedia.org/wiki/Dining_philosophers_problem

POSIX Threads Programming
https://man7.org/linux/man-pages/man7/pthreads.7.html

pthread_create
https://man7.org/linux/man-pages/man3/pthread_create.3.html

pthread_mutex_lock
https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

gettimeofday
https://man7.org/linux/man-pages/man2/gettimeofday.2.html

AI USAGE
AI was used as a learning assistant to understand multithreading concepts,
synchronization issues, and edge cases. All implementation and design decisions
were written and tested manually.