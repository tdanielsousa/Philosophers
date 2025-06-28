## Solution Architecture

The implementation uses a multi-threaded approach where each philosopher operates as an independent thread, with shared resources protected by mutex locks to ensure thread safety and prevent race conditions.  

![Solution Architecture](https://i.imgur.com/e6Obnof.png)

## Dining Philosophers Problem

A multi-threaded C application demonstrating concurrent programming concepts using POSIX threads and mutexes.

## Overview

This project simulates philosophers sitting around a circular table, alternating between eating, thinking, and sleeping.   
Each philosopher requires two forks to eat, creating a resource contention scenario that requires synchronization to prevent deadlocks and race conditions.

## Architecture

The system uses a thread-per-philosopher model with centralized monitoring:

    Main Thread: Manages initialization, thread creation, and simulation monitoring.

    Philosopher Threads: Execute eating, sleeping, and thinking cycles.

    Shared Resources: Fork mutexes and global simulation state.

## Array of Structs Implementation

The t_philo struct contains all data for each philosopher philo.h:74-88 :

    Individual philosopher ID, meal times, and fork assignments
    Pointer to shared simulation data
    Pointer to shared fork array

The array is allocated as a contiguous block ft_initialize.c:28 and each philosopher thread receives a pointer to its specific array element ft_simulation.c:42-43 .

## Key Features

    Deadlock Prevention: Ordered fork acquisition prevents circular dependencies.

    Thread-Safe Operations: Mutex-protected access to shared state.

    Death Monitoring: Real-time detection of philosopher starvation.

    Meal Completion Tracking: Automatic termination when all philosophers finish eating.
    
## Tester

I've also made a tester, which can just be download and ran via Makefile with make tester.


## Build & Usage

make                    # Build the project   
./philo 5 800 200 200   # 5 philosophers, 800ms death time, 200ms eat/sleep   
./philo 5 800 200 200 3 # Same setup, stop after 3 meals each   

## Core Components

    Initialization: System setup and resource allocation.

    Simulation Engine: Thread management and lifecycle control.

    Synchronization: Mutex-based thread safety.

    Timing System: Precise sleep and time measurement.
