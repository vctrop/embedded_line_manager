/**
 * @file triple_queue_gamb.h
 * @author Victor O. Costa
 * @author Robert Viaro
 * @author Lucas Domingues
 * @date 01 Jun 2012
 * @brief Header file for multiple queue management operations, implementing priority logic
 */
 
//#ifndef __MULT_QUEUE_H
//#define __MULT_QUEUE_H

#include <stdio.h>
#include "queue_gamb.h"

/**
 * @brief Defines the proportion between priority and normal line calls
 */
#define P2N_PROPORTION 3                                                            // priority to normal proportion

/**
 * @brief Function to initiate multiple queues
 */
void init_queue_mult();
/**
 * @brief Function to enqueue depending uppon priority
 */
void enqueue_mult(uint8_t priority, int8_t data);
/**
 * @brief Function to dequeue from multiple queues (taking priority in consideration)
 */
int8_t dequeue_mult();
/**
 * @brief Function to check if all queues are empty
 */
uint8_t is_all_empty();
/**
 * @brief Function to get the total quantity of members in the line
 */
uint8_t get_total_quant();
//int8_t get_front_mult(uint8_t priority);
//int8_t get_rear_mult(uint8_t priority);

//#endif