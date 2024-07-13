# Philosophers

Philosophers @ 1337 – 42 Network: a program that solves the dining philosophers problem

![Logo](./images/dining-philosophers.png)
## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)

## About <a name = "about"></a>

The Philosophers project, part of the 1337 – 42 Network curriculum, is a multithreading simulation of the classic dining philosophers problem.

This problem is a classic example of a common computing problem in concurrency that involves synchronization. In this project, we simulate a scenario where philosophers, represented as processes, are sitting around a table eating and thinking. They use forks to eat, but as there are only a certain number of forks available, they must share.

This project aims to solve the problem where each philosopher must get a chance to eat without causing a deadlock, where they are all holding a fork and waiting for another. The project is a great way to understand and implement concepts of multithreading, process synchronization, and deadlock prevention in a real-world scenario.

## Getting Started <a name = "getting_started"></a>

```
git clone git@github.com:lmakinaa/philosophers.git && cd philosophers
```
mutex-based solution: 
```
cd philo && make
```

semaphore-based solution: 
```
cd philo_bonus && make
```

### Prerequisites

To run the build and run the program, you'll need:
- Clang

## Usage <a name = "usage"></a>

```
./philo(_bonus) <number of philosophers> <time to die> <time to eat> <time to sleep> <optional: times must eat>
```

Where:
- number of philosophers: The number of philosophers and also the number of forks.
- time to die: If a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.
- time to eat: The time it takes for a philosopher to eat. During that time he will need to keep the two forks.
- time to sleep: The time the philosopher will spend sleeping.
- times must eat: If all philosophers eat at least ’times must eat’ times, the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.