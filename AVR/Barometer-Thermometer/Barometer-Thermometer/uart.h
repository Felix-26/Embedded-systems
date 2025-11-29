/*
 * uart.h
 *
 * Created: 11/3/2025 10:47:34 PM
 *  Author: felix
 */ 


#ifndef UART_H_
#define UART_H_


void uart_init(uint32_t BAUD);
void uart_tx(uint8_t c);
void uart_send_string(char *str);
void uart_send_hex(uint8_t hex);
void uart_send_int(uint32_t x);
void uart_send_32hex(uint32_t hex);


#endif /* UART_H_ */