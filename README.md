# Producer-Consumer Problem

This project implements the Producer-Consumer Problem using **C** with threads, semaphores, and shared memory.
The Problem models a scenario where two concurrent processes share a common, finite-size buffer, and enforces an instruction where 
the producer must wait if the buffer is full, and the consumer must also wait if the buffer is empty.
Both processes coordinate access to the buffer to avoid race conditions and ensures consistency with the data.
## Problem Description

- The producer generates items and adds them to a shared memory buffer.
- The consumer takes items from the buffer.
- The buffer has a fixed size of 2. The producer waits if the buffer is full, and the consumer waits if the buffer is empty.
- Semaphores ensure synchronization, and shared memory allows communication between the producer and consumer.

## Files

- `producer.c`: The producer program.
- `consumer.c`: The consumer program.
- `shared.h`: Shared definitions for buffer size, semaphores, and shared memory.


## Compilation

  
    gcc -pthread -o producer producer.c
    gcc -pthread -o consumer consumer.c

    ./producer & ./consumer &



## Screenhot

![image](https://github.com/user-attachments/assets/a522c403-fb0e-4a3b-96f7-0766e333e56c)

