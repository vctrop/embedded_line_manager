#include <uart_driver.h>
//----------------------------------------------
struct usart_module uart_modules[256];
struct usart_module uart_instance;

int usart_print(struct usart_module * uart_module, char character){
	usart_write_wait(uart_module, (uint16_t)character);
	
	return STATUS_OK;
}

void usart_scan(struct usart_module * uart_module, uint8_t * character){
    int i;
    for(i = 0; i < 5; i++){
        if(usart_read_buffer_wait(uart_module, character, sizeof(uint8_t))==STATUS_OK)
            break;
    }
}

void uart_config(uint8_t uart_num, uint32_t baudrate)
{
     struct usart_module uart_module;
    uart_modules[uart_num] = uart_module;
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.baudrate    = baudrate;
	usart_conf.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	usart_conf.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;	

	stdio_serial_init(&uart_modules[uart_num], EDBG_CDC_MODULE, &usart_conf);
	usart_enable(&uart_modules[uart_num]);
    
    ptr_put = (int (*)(void volatile*,char))&usart_print;
	ptr_get = (void (*)(void volatile*,char*))&usart_scan;
	
}
