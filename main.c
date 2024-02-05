#include <lpc214x.h>
#include "UART_lib.h"
#include "DHT11.h"
#include "lcd.h"
#include "adc.h"

char Sensor[5] = {0};
char datstr[100];

#define Moisture (IO1PIN & (1<<27))
#define WATER_PUMP_PIN 31
#define ldr_pin (IO1PIN & (1<<25))

unsigned int temp_th=40;

void initializeWaterPump()
{
   IODIR0 |= (1 << WATER_PUMP_PIN);
}

void turnOnWaterPump()
{
    IOSET0 = (1 << WATER_PUMP_PIN);
}

void turnOffWaterPump()
{
   IOCLR0 = (1 << WATER_PUMP_PIN);
}


int main()
{
	
	init_lcd(); //lcd Initialization
	initDHT();//DHT pin is connected at P0.30
	UART0_Init();//UART 0 Initialization
  
   initializeWaterPump();
	 GSM("Welcome");

while(1){

			delay_ms(100);
			if(fetchData(Sensor))
			{ 
				
			if(Sensor[2]>temp_th){
				
				UART0_String("Humidity:");
				TX0_Int(Sensor[0]);//Humidity
		    UART0_String(" ");
				UART0_String("Temperature:");
				TX0_Int(Sensor[2]);//temp
		    UART0_String("\r\n");
				
			}
				
				cmd_lcd(0x80);      // Sets the cursor to the beginning of the first line 
				string_lcd("H:");
		   	number_lcd(Sensor[0]);
				data_lcd('%');
				string_lcd(" ");
				string_lcd("T:");
				number_lcd(Sensor[2]);//temp
				data_lcd(0xDF);     //set the symbol for the temp
				data_lcd('C');
				cmd_lcd(0xC0);      //setting the cursor to the beginning of the second line
				
      }
			else
			{
			 UART0_String("ERROR ");
			}
		

     
		  if(Moisture) {
				            turnOnWaterPump();
										UART0_String("Low Moisture: Pump ON");
				            string_lcd("Pump ON");
				            UART0_String("\r\n");
				          
							   
            }
						else{   
										turnOffWaterPump();
							      UART0_String("High Moisture: Pump OFF");
							      string_lcd("Pump OFF");
							      UART0_String("\r\n");
							}
						

		

		 if(ldr_pin) {
            UART0_String("Intensity HIGH ");
			      UART0_String("\r\n");
			      string_lcd(", ");
			      string_lcd("DAY");
        } else {
            UART0_String("Intensity LOW");
					  UART0_String("\r\n");
					  string_lcd(", ");
					  string_lcd("NIGHT");
						
        }
				
	
}
}
