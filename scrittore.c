#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#include "buffer.h"

int main()
{
    printf("[%d] Avvio scrittore\n", getpid());

    key_t chiave_shm = 40; /* TODO: creazione chiave shared memory */

    int shm_id = shmget(chiave_shm, sizeof(buffer), IPC_CREAT | 0664); /* TODO: ottenere il descrittore della shared memory */

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b = shmat(shm_id);/* TODO: effettuare il collegamento (attach) della shared memory creata */

    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }

    key_t sem_chiave = 30; * TODO: creazione chiave semafori */

    int sem_id = semget(sem_chiave, 4, IPC_CREAT | 0664); /* TODO: ottenere il descrittore dell'array semaforico */

    if (sem_id < 0)
    {
        perror("Errore semget()");
        exit(1);
    }

    srand(getpid());

    for(int i=0; i<NUMERO_SCRITTURE; i++) {

        char val_1 = 'A' + rand() % 26;
        char val_2 = 'a' + rand() % 26;

        scrivi_buffer(b, sem_id, val_1, val_2);
    }

    return 0;

}
