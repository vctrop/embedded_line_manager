/**
 * @file queue_gamb.h
 * @author Victor O. Costa
 * @author Robert Viaro
 * @author Lucas Domingues
 * @date 01 Jun 2012
 * @brief Header file for single queue management operations
 */

#ifndef __QUEUE_H
#define __QUEUE_H

/**
 * @brief struct containing all informations of a single queue
 */
#define Q_SIZE 10
typedef struct{
    int8_t queue_vec[Q_SIZE];                // array containing the queue itself
    int8_t rear;                           // initial value of the queue rear is -1
    int8_t front;                          // initial value of thr queue front is -1
} Queue;

/**
 * @brief Function to initialize queue
 */
void init_queue(Queue *q);
/**
 * @brief Function to check if a queue is empty
 */
uint8_t is_empty(Queue *q);
/**
 * @brief Function to check if a queue is full
 */
uint8_t is_full(Queue *q);
/**
 * @brief Function to equeue
 */
uint8_t enqueue(Queue *q, int8_t data);
/**
 * @brief Function to dequeue 
 */
int8_t dequeue(Queue *q);
/**
 * @brief Queue getters 
 */
int8_t get_front(Queue *q);
int8_t get_rear(Queue *q);
int8_t get_front_index(Queue *q);

#endif