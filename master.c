#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "buffer.h"

int main() {

    printf("[%d] Creazione coda dei lettori\n", getpid());
    
    key_t chiave_queue = /* TODO: creazione chiave coda di messaggi */
    int queue = /* TODO: ottenere il descrittore della coda di messaggi */
    
    printf("[%d] Creazione shared memory\n", getpid());

    key_t chiave_shm = 40; /* TODO: creazione chiave shared memory */

    int shm_id = shmget(chiave_shm, sizeof(buffer), IPC_CREAT | 0664); /* TODO: ottenere il descrittore della shared memory */

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b = shmat(shm_id); /* TODO: effettuare il collegamento (attach) della shared memory creata */

    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }

    /* TODO: inizializzare il buffer condiviso e le variabili per la sincronizzazione */

    printf("[%d] Creazione semafori\n", getpid());

    key_t sem_chiave = 30; /* TODO: creazione chiave semafori */

    int sem_id = shmget(sem_chiave, 4, IPC_CREAT | 0664);/* TODO: ottenere il descrittore dell'array semaforico */

    if(sem_id < 0) {
        perror("Errore creazione semafori");
        exit(1);
    }

    /* TODO: Inizializzazione semafori per la sincronizzazione tra lettori e scrittori */
    semctl(sem_id, MUTEX, SETVAL, 1);
	semctl(sem_id, MUTEXS, SETVAL, 1);
	semctl(sem_id, MUTEXL, SETVAL, 1);
	semctl(sem_id, SYNCH, SETVAL, 1);
    
    printf("[%d] Creazione semafori corretta!\n", getpid());


    for(int i=0; i<NUM_SCRITTORI; i++) {
    
        printf("[%d] Creazione processo scrittore #%d\n", getpid(), i);
            
        /* TODO: creazione del processo scrittore tramite primitive della famiglia exec*/

    }
    

    for(int i=0; i<NUM_LETTORI; i++) {

        printf("[%d] Creazione processo lettore #%d\n", getpid(), i);
        
        /* TODO: creazione del processo lettore tramite primitive della famiglia exec */
    }

    /* TODO: attendere la ricezione dei messaggi da parte dei lettori e stamparli a video */
    
    printf("[%d] In attesa di terminazione dei processi\n", getpid());

    /* TODO: attendere la terminazione dei processi lettori e scrittori */

    printf("[%d] Deallocazione risorse\n", getpid());

    /* TODO: deallocazione delle risorse create */
    shmctl(shm_id, IPC_RMID, 0);
	shmctl(sem_id, 0, IPC_RMID);
}
