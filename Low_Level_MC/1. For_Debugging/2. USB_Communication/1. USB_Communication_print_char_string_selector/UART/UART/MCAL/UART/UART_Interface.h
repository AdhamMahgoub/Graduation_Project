#ifndef UART_INTERFACE
#define UART_INTERFACE


struct DataPackage
{
	char x; // 1 byte
	char y; // 1 byte
	char arr[30];
};

void UART_init(void);
void UART_TransmitData(u8 Data);
u8 UART_RecieveData(void);

void send_DataPackage_char(struct DataPackage *DataPackage_ptr);
void send_DataPackege_String(struct DataPackage *DataPackage_ptr);
void send_DataPackege_String_with_selector(struct DataPackage *DataPackage_ptr, char selector);

#endif
