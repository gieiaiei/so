#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "buffer.h"


void send_values(char *char_1, char *char_2, int queue){
    
    Messaggio m;
    
    /* TODO: costruzione del messaggio da trasmettere */
    
    /* TODO: invio messaggio */
    
}

void leggi_buffer(buffer * b, int sem_id, char *char_1, char *char_2, int queue) {

    /* TODO: Inizio lettura */
    Wait_Sem(sem_id, MUTEXL);
    NUM_LETTORI++;
    if(NUM_LETTORI==1) Wait_Sem(sem_id, SYNCH);
    Signal_Sem(sem_id, MUTEXL);
    
    
    printf("[%d] Lettura buffer: char_1 = %c, char_2 = %c\n", getpid(), b->char_1, b->char_2);

    sleep(1);

    //LETTURA dei caratteri e conversione
    *char_1 = b->char_1 + 32;
    *char_2 = b->char_2 - 32;
    
    send_values(char_1, char_2, queue);

    /* TODO: Fine lettura */
    Wait_Sem(sem_id, MUTEXL);
    NUM_LETTORI--;
    if(NUM_LETTORI==0) Signal_Sem(sem_id, SYNCH);
    Signal_Sem(sem_id, MUTEXL);
}

void scrivi_buffer(buffer *b, int sem_id, char char_1, char char_2) {

    /* TODO: Inizio scrittura */
    Wait_Sem(sem_id, MUTEXS);
    NUM_SCRITTORI++;
    if(NUM_SCRITTORI==1) Wait_Sem(sem_id, SYNCH);
    Signal_Sem(sem_id, MUTEXS);
    Wait_Sem(sem_id, MUTEX);
    
    printf("[%d] Scrittura buffer: char_1 = %c, char_2 = %c\n", getpid(), char_1, char_2);

    /* TODO: SCRITTURA dei caratteri sul buffer condiviso */
    
    
    b->char_1 = char_1;
    b->char_2 = char_2;

    /* TODO: Fine scrittura */
    Signal_Sem(sem_id, MUTEX);
    Wait_Sem(sem_id, MUTEXS);
    NUM_SCRITTORI--;
    if(NUM_SCRITTORI == 0) Signal_Sem(sem_id, SYNCH);
    Signal_Sem(sem_id, MUTEXS);
    
}
