#ifndef SHARED_H
#define SHARED_H

#define SHM_NAME "/shared_table"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"
#define BUFFER_SIZE 2
#define MAX_ITEMS 20

struct SharedTable {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
};

#endif
