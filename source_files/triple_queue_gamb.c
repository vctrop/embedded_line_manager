/*
File implementing a system to manage three queues, each with a different priority level (0, 1, 2, from lowest to highest).
*/
#include "triple_queue_gamb.h"
#include "queue_gamb.h"

Queue normal_q;                                                                     // no priority
Queue priority_q;                                                                   // priority
Queue elder_q;                                                                      // greater priority (>80 years old)

int priority_counter = 0;                                                           // the basis to select from which queue to pull

void init_queue_mult(){
    init_queue(&normal_q);
    init_queue(&priority_q);
    init_queue(&elder_q);
}

void enqueue_mult(uint8_t priority, int8_t data){
    switch(priority){
        case 0:                                                                     // normal queue
            enqueue(&normal_q, data);
            break;

        case 1:                                                                     // priority queue
            enqueue(&priority_q, data);
            break;

        case 2:
            enqueue(&elder_q, data);                                                // elder priority queue (>80 years old)
            break;

        default:
            //printf("Wrong priority, please enter an 0, 1 or 2\n");
            break;
    }
}

int8_t dequeue_mult(){
    int8_t dequeued_value;

    if(!is_empty(&elder_q)){                                                        // if there is someone in elder queue
        dequeued_value = dequeue(&elder_q);
    }
    else if(is_empty(&normal_q)){                                                   // if normal queue is empty
            if(is_empty(&priority_q)){
                //printf("Error, all queues are empty (returning -1)\n");
                dequeued_value = -1;
            }
            else{
                dequeued_value = dequeue(&priority_q);
                priority_counter++;
            }
    }
    else{
        if((priority_counter >= P2N_PROPORTION) || is_empty(&priority_q)){                                     // after dequeuing priority P2N_PROPORTION times, dequeue normal
            dequeued_value = dequeue(&normal_q);
            priority_counter = 0;
        }
        else{
            dequeued_value = dequeue(&priority_q);
            priority_counter++;
        }
    }

    return dequeued_value;
}

uint8_t is_all_empty(){
    return (is_empty(&normal_q) && is_empty(&priority_q) && is_empty(&elder_q));
} 

/*int8_t get_front_mult(uint8_t priority){
    int8_t front_value;
    switch(priority){
        case 0:                                                                     // normal queue
            front_value = get_front(&normal_q);
            break;

        case 1:                                                                     // priority queue
            front_value = get_front(&priority_q);
            break;

        case 2:                                                                     // elder priority queue (>80 years old)                                               
            front_value = get_front(&elder_q);
            break;

        default:
            //printf("Wrong priority, please enter 0, 1 or 2 (returning (u)-2)\n");
            front_value = -2;
            break;
            
    return front_value;
}

int8_t get_rear_mult(uint8_t priority){
    int8_t rear_value;
    switch(priority){
        case 0:                                                                     // normal queue
            rear_value = get_rear(&normal_q);
            break;

        case 1:                                                                     // priority queue
            rear_value = get_rear(&priority_q);
            break;

        case 2:                                                                     // elder priority queue (>80 years old)                                                   
            rear_value = get_rear(&elder_q);
            break;

        default:
            //printf("Wrong priority, please enter 0, 1 or 2 (returning (u)-2)\n");
            rear_value = -2;
            break;
            
    return rear_value;
}*/

uint8_t get_total_quant() {
    uint8_t sum = 0;
    int8_t rear, front, ind;
    
    // Calculates normal queue quantity
	ind = get_front_index(&normal_q);
    if(ind != -1){
		front = get_front(&normal_q);
        rear = get_rear(&normal_q);
        sum += rear - front + 1;
    }
    
    // Calculates priority queue quantity
    ind = get_front_index(&priority_q);
    if(ind != -1){
	    front = get_front(&priority_q);
	    rear = get_rear(&priority_q);
	    sum += rear - front + 1;
    }
    
    // Calculates elder queue quantity
	ind = get_front_index(&elder_q);
	if(ind != -1){
		front = get_front(&elder_q);
		rear = get_rear(&elder_q);
		sum += rear - front + 1;
	}
    
    return sum;
}

/*
uint8_t emptiness[EEPROM_PAGE_SIZE];
emptiness[0] = is_all_empty();
eeprom_emulator_write_page(0, emptiness);
eeprom_emulator_commit_page_buffer();

eeprom_emulator_read_page(0, emptiness);

////////////////////////////
// writing to flash

uint8_t normal_vec[EEPROM_PAGE_SIZE];
uint8_t priority_vec[EEPROM_PAGE_SIZE];
uint8_t elder_vec[EEPROM_PAGE_SIZE];

normal_vec[0] = is_empty_mult(0);
if(!is_empty_mult(0)){                                      // if normal queue was not empty
    normal_vec[1] = get_front_mult(0);
    normal_vec[2] = get_rear_mult(0);
}

priority_vec[0] = is_empty_mult(1);
if(!is_empty_mult(1)){                                      // if priority queue was not empty
    priority_vec[1] = get_front_mult(1);
    priority_vec[2] = get_rear_mult(1);
}

elder_vec[0] = is_empty_mult(2);
if(!is_empty_mult(2)){                                       // if elder queue was not empty
    elder_vec[1] = get_front_mult(2);
    elder_vec[2] = get_rear_mult(2);
}

eeprom_emulator_write_page(0, normal_vec);
eeprom_emulator_write_page(1, priority_vec);
eeprom_emulator_write_page(2, elder_vec);

// reading from flash and recreating queue
uint8_t rear, front;

eeprom_emulator_read_page(0, normal_vec);
if(!normal_vec[0]){                                 // if normal queue was not empty
    front = normal_vec[1];
    rear = normal_vec[2];
}

eeprom_emulator_read_page(1, priority_vec);
if(!priority_vec[0]){                                 // if priority queue was not empty
    front = priority_vec[1];
    rear = priority_vec[2];
}

eeprom_emulator_read_page(2, elder_vec);
if(!elder_vec[0]){                                 // if elder queue was not empty
    front = elder_vec[1];
    rear = elder_vec[2];
}
*/


