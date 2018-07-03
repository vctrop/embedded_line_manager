/**
 * @file main.c
 * @author Victor O. Costa
 * @author Robert Viaro
 * @author Lucas Domingues
 * @date 01 Jun 2012
 * @brief The main file of the project, containing the FSM with pointers structure.
 */

#include <asf.h>
#include <string.h>
#include "triple_queue_gamb.h"
#include "uart_driver.h"
#include "demotasks.h"

/**
 * @brief State definitions
 */
#define ST_NEXT 0
#define ST_BUTTON 1
#define ST_DISPLAY 2

typedef void (*callback)();
callback state_functions[3];
short int state = ST_BUTTON;

/**
 * @brief Global line variables 
 */
int8_t dequeued_val = -1;
int8_t normal_number = 10;
int8_t priority_number = 20;
int8_t elder_number = 30;
int8_t last_registered = -1;


/**
 * @brief OLed drawing operations 
 */
static OLED1_CREATE_INSTANCE(oled1, EXT1);
int x = 0, y = 0;
void ativar_oled(void)
{
	// Initialize hardware for the OLED1 Xplained Pro driver instance
	gfx_mono_init();
	oled1_init(&oled1);
}

void oled_wrt_char(char c){
	if (x>125)
		x=0;

	gfx_mono_draw_char(c , x, y, &sysfont);
	x=x+7;
}

void oled_wrt_word(const char* word, int line){
    int len, i;
    len = strlen(word);
	y = line*8;
    for(i = 0; i < len; i++)
	     oled_wrt_char(word[i]);
}
/**
 * @brief State callback, waits for the "next" call from UART
 */
void st_wait_next(){
	char data;
	
	uint8_t remain;
	scanf("%c",&data);
	if(data=='p'){
		dequeued_val = dequeue_mult();
		remain = get_total_quant();
		
		printf("%d;%d\r",dequeued_val,remain);              // manda dados da fila e quantidade de elementos sempre \r no final

		data='x';
	}
	state = ST_BUTTON;
}

/**
 * @brief State callback, waits for the button interactions, inserting new members in the line
 */
void st_wait_buttons(){
	int8_t quantity;
	static int8_t first_pass = 1;
	
    if (oled1_get_button_state(&oled1, OLED1_BUTTON1_ID)){
		while(oled1_get_button_state(&oled1, OLED1_BUTTON1_ID)){}
        enqueue_mult(0, normal_number);
		
		last_registered = normal_number;
        normal_number++;
		
		quantity = get_total_quant();
		printf("%d;%d\r",dequeued_val, quantity);
    } else if (oled1_get_button_state(&oled1, OLED1_BUTTON2_ID)){
		while(oled1_get_button_state(&oled1, OLED1_BUTTON2_ID)){}
        enqueue_mult(1, priority_number);

		last_registered = priority_number;
        priority_number++;
		
		quantity = get_total_quant();
		printf("%d;%d\r",dequeued_val, quantity);
    } else if (oled1_get_button_state(&oled1, OLED1_BUTTON3_ID)){        
		while(oled1_get_button_state(&oled1, OLED1_BUTTON3_ID)){}
        
		
        if(first_pass){
			first_pass = 0;
		}
		else{
			enqueue_mult(2, elder_number);
			last_registered = elder_number;
			elder_number++;
		}
		quantity = get_total_quant();
		printf("%d;%d\r",dequeued_val, quantity);
        
    }
    
    state = ST_DISPLAY;
}


/**
 * @brief State callback, refreshing the OLED display
 */
void st_refresh_display(){
    char line[18];
    char itoa_buffer[3];
    
    strcpy(line, "   LINE MANAGER   ");
    oled_wrt_word(line, 0);
    
    strcpy(line, "Calling: ");
    itoa(dequeued_val, itoa_buffer, 10);
    strcat(line, itoa_buffer);
	strcat(line,"       ");
    oled_wrt_word(line, 2);
    
    strcpy(line, "Last: ");
    itoa(last_registered, itoa_buffer, 10);
    strcat(line, itoa_buffer);
	strcat(line,"          ");
    oled_wrt_word(line, 3);
    
    state = ST_NEXT;
}

/**
 * @brief Main function
 */
int main(void)
{
	system_init();
	uart_config(1, 9600);
    ativar_oled();
    init_queue_mult();
    
	state_functions[ST_BUTTON] = st_wait_buttons;
    state_functions[ST_NEXT] = st_wait_next;
	state_functions[ST_DISPLAY] = st_refresh_display;
    
	while (true) {
		state_functions[state]();
	}
}