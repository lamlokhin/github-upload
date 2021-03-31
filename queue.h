/*
* File: queue.h
*/
typedef struct customer *customerT;
typedef struct queueCDT *queueADT;
typedef customerT queueElementT;


queueADT emptyQueue(void);
void enqueue(queueADT queue, queueElementT element);
queueElementT dequeue(queueADT queue);
int queueLength(queueADT queue);
int queueIsEmpty(queueADT queue);

