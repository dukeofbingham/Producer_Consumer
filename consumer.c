#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include "shared.h"

int main() {
    // opens a shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    struct SharedTable *table = (struct SharedTable *)mmap(NULL, sizeof(struct SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // open semaphores
    sem_t *empty = sem_open(SEM_EMPTY, 0);
    sem_t *full = sem_open(SEM_FULL, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, 0);

    if (empty == SEM_FAILED || full == SEM_FAILED || mutex == SEM_FAILED) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    printf("Consumer initialized successfully.\n");

    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(full); // wait if the buffer is empty
        sem_wait(mutex); // ensure mutual exclusion

        int item = table->buffer[table->out];
        printf("Consumed: %d from index %d\n", item, table->out);
        table->out = (table->out + 1) % BUFFER_SIZE;

        sem_post(mutex); // release mutex
        sem_post(empty); // signal that a slot is now empty

        sleep(1); // simulate consumption delay
    }

    printf("Consumer finished.\n");

    // Cleanup
    munmap(table, sizeof(struct SharedTable));
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);

    return 0;
}
