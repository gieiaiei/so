#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "semafori.h"

#define NUM_LETTORI 5
#define NUM_SCRITTORI 3
#define NUMERO_LETTURE 5
#define NUMERO_SCRITTURE 5

/* TODO: definire le macro necessarie per la sincronizzazione e lo scambio di messaggi su coda */
#define MUTEXL 1
#define MUTEXS 1
#define MUTEX 1
#define SYNCH 1

typedef struct {
    /* TODO: definire i campi del buffer condiviso e le varibili di sincronizzazione */
    char val_1;
    char val_2;
} buffer;

typedef struct {
    /* TODO: definire i campi dei messaggi scambiati tra lettori e master */
} Messaggio;

void leggi_buffer(buffer * b, int sem_id, char *val_1, char *val_2, int queue);
void scrivi_buffer(buffer *b, int sem_id, char val_1, char val_2);

#endif
