/*******************************************************************************************************************
This program read values from sensors and displays an 8 element array onto the LCD screen by using "lcd_array.h"
********************************************************************************************************************/

#include<intrins.h>
#include"p89v51rx2.h"
#include"LCD_ARRAY.h"

sbit start_conv = P3^6;		 //P3^6 is connected to Start and ALE pin of ADC0808
sbit output_enable = P3^7;		 //P3^7 is connected to Output Enable Pin of ADC0808

unsigned char data_array[8];//initialize an array of 8 elements to display onto the LCD screen
unsigned char i=0;  //used in main function during ADC conversion 

/********************************************************************************
	Function: ADC_conversion(unsigned char ADC_channel_number)

	Description: This function performs ADC conversion of a channel number 
				 that is passed to it. The return value of this function contains 
 				 digital data of the selected channel.
		   
				 Analog Sensor Pin Mapping
  
       			 IN0-----> IR Proximity sensor 3 (front)
				 IN1-----> Batt. Voltage
				 IN2-----> Front Sharp IR Range sensor
				 IN3-----> IR Proximity sensor 2 (left side)
				 IN4-----> Left Whiteline
		 		 IN5-----> Center Whiteline
				 IN6-----> Right Whiteline
				 IN7-----> IR Proximity sensor 4 (right side)
********************************************************************************/
unsigned char ADC_conversion(unsigned char ADC_ch_no)
{
unsigned char ADC_data;

P0 = ADC_ch_no;	// to select channel no. send address on P0

start_conv = 1; // ADC0808 will latch the address on L-H transition on the ALE pin
start_conv = 0;	// ADC0808 will start conversion on H-L transition on the start pin
delay_ms(2);	// conversion time for ADC0808

P0 =0xFF;	        // output enable and read
output_enable = 1;	//Enabling o/p of ADC0808 for to read the converted data
ADC_data = P0;		//storing adc_data
output_enable = 0;	//disabling ADC 0808 o/p
return ADC_data;	//returning adc_data
}



void main()
{
 unsigned char i=0;
 output_enable = 0;
 start_conv = 0;    //de-assert all control signals to ADC
 
 LCD_INIT(); //Initialize LCD

 while(1)
 {
  for(i=0;i<8;i++)
  {
  data_array[i] = ADC_conversion(i);
  }
  
  LCD_PRINT(data_array);//call this function to print the array onto the screen
  delay_ms(500);
 }
}