#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

	void I2C_Init_Master(void);
	void I2C_Init_Slave(void);
	void I2C_Start(void);
	void I2C_Repeated_Start(void);
	void I2C_Write_data(u8 data);
	u8   I2C_Read_data(void);
	void I2C_Stop(void);
	void I2C_Send_slave_address_with_write_req(u8 slave_address);
	void I2C_Send_slave_address_with_read_req(u8 slave_address);

#endif
