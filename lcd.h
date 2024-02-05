#ifndef _LCD_H
#define _LCD_H

#define DATA_PORT_SET       IOSET0
#define DATA_PORT_CLR       IOCLR0
#define DATA_DIR            IODIR0
#define D7					19
#define D6					18
#define D5					17
#define D4					16
#define D3					15
#define D2					14
#define D1					13
#define D0					12
//Set data port pins
#define DATA_PORT    				(unsigned long)((1<<D7)|(1<<D6)|(1<<D5)|(1<<D4))|((1<<D3)|(1<<D2)|(1<<D1)|(1<<D0))

#define CTRL_PORT_SET       IOSET0
#define CTRL_PORT_CLR       IOCLR0
#define CTRL_DIR            IODIR0
#define CTRL_RS             20
#define CTRL_EN             21

void delay_us(unsigned int count);
void delay_ms(unsigned int count);
void cmd_lcd(unsigned char byte);
void data_lcd(unsigned char byte);
void init_lcd();
void string_lcd(char *str);
void number_lcd(int num)  ;

#endif
