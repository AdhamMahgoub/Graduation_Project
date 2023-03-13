/*Copyright (c) 2018 qb4.dev@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "../avr-hw-i2c/i2cmaster.h" //path to i2c fleury lib

#include "qmc5883l.h"

void qmc5883l_write_reg(uint8_t reg, uint8_t val)
{
	i2c_start(QMC5883L_ADDR | I2C_WRITE);
	i2c_write(reg);
	i2c_write(val);
	i2c_stop();
}

void qmc5883l_init(void)
{
	#if QMC5883L_I2C_INIT == 1
	i2c_init();
	_delay_us(10);
	#endif

	qmc5883l_write_reg(QMC5883_REG_SET_RESET,0x01);
	qmc5883l_set_config(QMC5883_MODE_CONTINOUS, ODR_200Hz,RNG_8G,OSR_512);
}

void qmc5883l_set_config(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr)
{
	qmc5883l_write_reg(QMC5883_REG_CONFIG_1,mode|odr|rng|osr);
}


void qmc5883l_getrawdata(int16_t *mx, int16_t *my, int16_t *mz)
{
	uint8_t i = 0;
	uint8_t buff[6];

	i2c_start(QMC5883L_ADDR | I2C_WRITE);
	i2c_write(0x00);
	i2c_stop();
	i2c_rep_start(QMC5883L_ADDR | I2C_READ);
	for(i=0; i<6; i++) {
		buff[i] = (i==5)?i2c_readNak():i2c_readAck();
	}
	i2c_stop();

	*mx = (int16_t)((buff[1] << 8) | buff[0]);
	*my = (int16_t)((buff[3] << 8) | buff[2]);
	*mz = (int16_t)((buff[5] << 8) | buff[4]);
}

float qmc5883l_calc_heading(int16_t mx, int16_t my)
{
	float heading = atan2((double)my,(double)mx)*180.0/M_PI;

	return (heading < 0)? 360 + heading:heading;
}
