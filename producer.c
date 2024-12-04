#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include "shared.h"

int main() {
    // opens a shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct SharedTable));
    struct SharedTable *table = (struct SharedTable *)mmap(NULL, sizeof(struct SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize shared memory
    table->in = 0;
    table->out = 0;

    // Open semaphores
    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFFER_SIZE);
    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    if (empty == SEM_FAILED || full == SEM_FAILED || mutex == SEM_FAILED) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    printf("Producer initialized successfully.\n");

    for (int i = 0; i < MAX_ITEMS; i++) {
        int item = rand() % 100; // Generate a random item

        sem_wait(empty); // Wait if the buffer is full
        sem_wait(mutex); // Ensure mutual exclusion

        table->buffer[table->in] = item;
        printf("Produced: %d at index %d\n", item, table->in);
        table->in = (table->in + 1) % BUFFER_SIZE;

        sem_post(mutex); // release mutex
        sem_post(full);  // signal that a new item is available

        sleep(1); // simulate production delay
    }

    printf("Producer finished.\n");

    // Cleanup
    munmap(table, sizeof(struct SharedTable));
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);

    return 0;
}
