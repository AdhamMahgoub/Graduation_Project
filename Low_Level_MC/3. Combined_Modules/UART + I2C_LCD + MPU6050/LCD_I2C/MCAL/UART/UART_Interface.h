#ifndef UART_INTERFACE
#define UART_INTERFACE


struct DataPackage
{
	char Xa; // 1 byte
	char Ya; // 1 byte
	char Za; // 1 byte
	char Xg; // 1 byte
	char Yg; // 1 byte
	char Zg; // 1 byte
	char t; // 1 byte

	char arr[30];
};

void UART_init(void);
void UART_TransmitData(u8 Data);
u8 UART_RecieveData(void);

void send_DataPackage_char(struct DataPackage *DataPackage_ptr);
void send_DataPackege_String(struct DataPackage *DataPackage_ptr);
void send_DataPackege_String_with_selector(struct DataPackage *DataPackage_ptr, char selector);

#endif
