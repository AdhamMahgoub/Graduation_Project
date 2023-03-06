#ifndef UART_INTERFACE
#define UART_INTERFACE

void UART_init(void);
void UART_TransmitData(u8 Data);
u8 UART_RecieveData(void);

#endif
