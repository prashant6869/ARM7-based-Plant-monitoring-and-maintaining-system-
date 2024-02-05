
#ifndef _UART_lib_H
#define _UART_lib_H

#define PCLK 15000000

void GSM(char String[]);
void UART0_Init(void);
void UART0_TX(char data);
char UART0_RX(void);
void UART0_String(char String[]);
void UART0_Char_Response(char data);
void TX0_Int(int INT);

#endif
