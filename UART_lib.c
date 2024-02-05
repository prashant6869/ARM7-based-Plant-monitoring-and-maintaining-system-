
#include<lpc214x.h>
#include "UART_lib.h"

void GSM(char String[]){

 UART0_String("AT\r\n");
 UART0_String("AT+CMGF=1\r\n");//Send SMS: Select Text mode
 UART0_String("AT+CMGS=\"7499209038" "\r\n"); //Send SMS to mobile number  
 UART0_String(String);
 UART0_String("\r\n");

} 

void UART0_Init(void)
{
    PINSEL0|=0x5;  
	U0LCR=0x83;   //line control register
	U0DLL=0x61;    //
	U0DLM=0x00;
	U0LCR=0x03;
}
void UART0_TX(char data)
{
	while(!(U0LSR&0x20));        
    U0THR=data;               
}
char UART0_RX(void)
{       
    char p;
	while(!(U0LSR&0x01));
	p=U0RBR;               //receiver buffer resistor      
	return p;
}
void UART0_String(char String[])
{
    unsigned char i;
	for(i=0;String[i]!='\0';i++)
	{
		UART0_TX(String[i]);
	}
}
void UART0_Char_Response(char data)
{
	char Received_char;
	Received_char = UART0_RX();
	while(Received_char != data)
	{
		Received_char = UART0_RX();
	}
}
void TX0_Int(int INT)
{
	
	UART0_TX(((INT%1000)%100)/10 + 48);
	UART0_TX(((INT%1000)%100)%10 + 48);
}
