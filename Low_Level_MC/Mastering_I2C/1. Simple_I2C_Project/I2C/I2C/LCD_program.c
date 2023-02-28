#include "STD_TYPES.H"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LCD_interface.h"

#include <util/delay.h> 	//need to include delay -- will be added in the main.c file 


void LCD_voidInit(void)
{ 
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xFF); 		//all pins are OUTPUT (DATA_PORT)
	//DIO_voidSetPortDirection(LCD_CONTROL_PORT, 0xFF); 	//all pins are OUTPUT (CONTROL_PORT)
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, PIN0, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, PIN1, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, PIN2, OUTPUT);
	
	_delay_ms(45); 				/*	LCD Power ON delay always > 15ms	*/
											
	LCD_voidSendCMD (function_set);		    	//function set 					Initialization of 16x2 LCD in 8 bit mode 
	LCD_voidSendCMD (display_on_off_control);	//display on/off control      	Display ON Cursor OFF  
	LCD_voidSendCMD (entry_mode_set);		    //entry mode set              	Auto Increment Cursor 
	LCD_voidSendCMD (clear_display);		    //clear display              	Clear display  
	LCD_voidSendCMD (set_DDRAM_address);		//set DDRAM address         	Cursor at home position 
											
}

void LCD_voidSendCMD(u8 CMD)
{
	/*- Conditions to send cmd 
    1. RS 	= 0 
    2. RW 	= 0
    3. EN 	= pulse 
    4. DATA =  CMD
	*/
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, LOW);		/*		1- RS = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, LOW);		/*		2- RW = 0		*/
	/*		3- EN pulse		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, HIGH);
	/*		4- SEND CMD		*/
	DIO_voidSetPortValue(LCD_DATA_PORT, CMD);
	_delay_ms(20);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, LOW);
	_delay_ms(20);										
}

void LCD_voidWriteData(u8 Data)
{
	/*- Conditions to send cmd 
    1. RS 	= 1 
    2. RW 	= 0
    3. EN 	= pulse 
    4. DATA =  CMD
	*/
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, HIGH); 	/*		1- RS = 1		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, LOW);		/*		2- RW = 0		*/
	/*		3- EN pulse		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, HIGH);
	/*		4- SEND CMD		*/
	DIO_voidSetPortValue(LCD_DATA_PORT, Data);
	_delay_ms(50);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, LOW); 
	_delay_ms(50);										
}

void LCD_cursor_shift_right (void)
{
	LCD_voidSendCMD(cursor_shift_right);
}

void LCD_set_xy (u8 row, u8 column)
{	
	//shifting y (row -- horizontal) 
	if (row == 1)
		LCD_voidSendCMD(DDRAM_to_2nd_row); //sends the DDRAM to the 2nd row 

	
	//shifting x (column -- vertical)
	for (int i=0; i<column; i++)
	{
		LCD_cursor_shift_right();
	}	
}

void LCD_clear(void)						//done by me 
{
	  LCD_voidSendCMD(clear_display);
}

void LCD_print_string(const char *str)		//copied from github + modified by me 
{
	/*	Without using "const", str was stored in flash memory (with the code)	*/
	/*	when i used const, it moved from flash memory to the RAM				*/
	
	unsigned char i = 0;
	
	while(str[i] != 0)
	{
		LCD_voidWriteData(str[i]);
		i++;
	}
}

void LCD_write_num(u32 num)					//copied from github + modified by me
{			
	u32 txt[10] = {0};
	s16 i = 0;
	if(num == 0) 
	{
		LCD_voidWriteData('0');
		return; //end the function
	}
	
	for (i = 0; num != 0; i++ )
	{
		txt[i] = num%10 + 48;
		num = num  / 10 ;
	}
	i--;
	
	while(i >= 0)
	{
		LCD_voidWriteData(txt[i]);
		i--;
	}
}