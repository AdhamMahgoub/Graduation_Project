#ifndef			LCD_INTERFACE_H 
#define 		LCD_INTERFACE_H

#define 		LCD_DATA_PORT			PORTA		//the whole 8 bits 
#define			LCD_CONTROL_PORT		PORTB		//only 3 bits 

#define			LCD_RS					PIN0
#define			LCD_RW					PIN1
#define			LCD_EN					PIN2

#define 		function_set			0b00111000
#define			display_on_off_control 	0b00001110
#define			entry_mode_set 			0b00000110
#define			clear_display           0b00000001
#define			set_DDRAM_address		0b10000000
#define 		cursor_shift_right  	0b00010100
#define 		DDRAM_to_2nd_row 		0b11000000
                                        

void LCD_voidInit(void);
void LCD_voidSendCMD(u8 CMD);
void LCD_voidWriteData(u8 Data);

/*the following are functions done by me*/
void LCD_cursor_shift_right (void);
void LCD_set_xy(u8 x, u8 y);
void LCD_clear(void);					//done by me 
void LCD_print_string(const char *str); //copied from github + modified by me 
void LCD_write_num(u32 num);			//copied from github + modified by me 

/*  Example on how to use the Functions

    LCD_voidInit(void);
    LCD_voidSendCMD(CMD);
    LCD_voidWriteData(DATA);

*/

#endif

