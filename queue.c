/*
* File: queue.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


typedef struct cellT {
    queueElementT value;
    struct cellT *next;
} cellT;

struct queueCDT {
    cellT *front;
    cellT *rear;
};

queueADT emptyQueue(void){
    queueADT queue;

    queue = (queueADT)malloc(sizeof(*queue));
    queue->front = NULL;
    queue->rear = NULL;
    return(queue);
}

void enqueue(queueADT queue, queueElementT element){
    cellT *cp = (cellT*)malloc(sizeof(cellT));
    cp->value = element;
    cp->next=NULL;
    if (queue->front == NULL)
        queue->front = cp;
    else
        queue->rear->next = cp;
    queue->rear = cp;
}

queueElementT dequeue(queueADT queue){
    queueElementT result;

    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    };

    result = queue->front->value;
    queue->front = queue->front->next;

    return(result);
}

int queueLength(queueADT queue){
    int n = 0; cellT *cp;
    for(cp = queue->front; cp!=NULL; cp = cp->next) n++;
    return(n);
}

int queueIsEmpty(queueADT queue) {
return(queue->front==NULL);
}
