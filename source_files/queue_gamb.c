/*
Author: Victor O. Costa
Queue implementation using circular array.
Data is inserted at rear and removed at front.
*/


#include <stdio.h>
#include "queue_gamb.h"

void init_queue(Queue *q){
    q->rear = -1;
    q->front = -1;
}

/* Verifies if the given queue is empty*/
uint8_t is_empty(Queue *q){
    return (q->rear == -1 && q->front == -1);               // if rear and front are both -1, queue is empty
}

/* Verifies if the given queue is full*/
uint8_t is_full(Queue *q){
    return ((q-> rear + 1)%Q_SIZE == q->front);                  // if the circular increment of rear is equal to front, queue is full
}

uint8_t enqueue(Queue *q, int8_t data){
    if(is_full(q)){
        //printf("ERROR, queue is full, can't enqueue %d\n",data);
        return 0;
    }
    else if(is_empty(q)){                                   // if queue is empty, initialize
        q->front = q->rear = 0;
    }
    else{
        q->rear = (q->rear + 1)%Q_SIZE;                          // else, update (in a circular way) its rear
    }
    q->queue_vec[q->rear] = data;                           // assign data to the current queue rear
    return 1;
}

int8_t dequeue(Queue *q){
    int8_t front_value;

    if(is_empty(q)){
        //printf("Error, queue is empty (will return -1)\n");
        front_value = -1;
    }
    else{                                                   // if queue isn't empty
        front_value = q->queue_vec[q->front];
        if(q->front == q->rear)                           // if queue has only one element
            q->front = q->rear = -1;
        else
            q->front = (q->front+1)%Q_SIZE;

    }
    return front_value;

}


int8_t get_front(Queue *q){
    if(!is_empty(q))
        return q->queue_vec[q->front];
    else{
        printf("Error, queue is empty");
        return -1;
    }
}

int8_t get_rear(Queue *q){
    if(!is_empty(q))
        return q->queue_vec[q->rear];
    else{
        printf("Error, queue is empty");
        return -1;
    }
}

int8_t get_front_index(Queue *q){
	return q->front;
}