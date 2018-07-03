/**
 * @file uart_driver.h
 * @author Victor O. Costa
 * @author Robert Viaro
 * @author Lucas Domingues
 * @date 01 Jun 2012
 * @brief Header file for the UART serial communication
 */

#include <stdio_serial.h>
#include <asf.h>

/**
 * @brief Print USART callback 
 */
int usart_print(struct usart_module * uart_module, char character);
/**
 * @brief Scan USART callback 
 */
void usart_scan(struct usart_module*, uint8_t * character);
/**
 * @brief Sets initial USART configs 
 */
void uart_config(uint8_t uart_num, uint32_t baudrate);


void usart_read_callback(struct usart_module *const usart_module);
void usart_write_callback(struct usart_module *const usart_module);