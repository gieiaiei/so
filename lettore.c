#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "buffer.h"

int main()
{
    printf("[%d] Avvio lettore\n", getpid());

    key_t chiave_queue = 20; /* TODO: creazione chiave coda di messaggi */
    
    int queue = /* TODO: ottenere il descrittore della coda di messaggi */
    
    key_t chiave_shm = 40; /* TODO: creazione chiave shared memory */

    int shm_id = shmget(chiave_shm, sizeof(buffer), IPC_CREAT | 0664);

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b = shmat(shm_id);
    
    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }


    key_t sem_chiave = 30; /* TODO: creazione chiave per l'array semaforico */

    int sem_id = semget(sem_chiave, 4, IPC_CREAT | 0664); /* TODO: ottenere il descrittore dell'array semaforico */

    if (sem_id < 0)
    {
        perror("Errore semget()");
        exit(1);
    }


    srand(getpid());

    for(int i=0; i<NUMERO_LETTURE; i++) {

        char val_1 = '\0';
        char val_2 = '\0';

        leggi_buffer(b, sem_id, &val_1, &val_2, queue);
        
        
    }



    return 0;

}
