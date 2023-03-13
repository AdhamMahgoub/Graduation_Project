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

/*
 	In some GY-271 boards QMC5883L is used instead HMC5883L
	https://img.filipeflop.com/files/download/Datasheet-QMC5883L-1.0%20.pdf
*/

#ifndef QMC5883L_H_
#define QMC5883L_H_

#define QMC5883L_ADDR                (0x0D <<1) //device address
#define QMC5883L_I2C_INIT 0          //init i2c during chip init

#define QMC5883_REG_OUT_X_LSB        (0x00)
#define QMC5883_REG_OUT_X_MSB        (0x01)
#define QMC5883_REG_OUT_Y_LSB        (0x02)
#define QMC5883_REG_OUT_Y_MSB        (0x03)
#define QMC5883_REG_OUT_Z_LSB        (0x04)
#define QMC5883_REG_OUT_Z_MSB        (0x05)
#define QMC5883_REG_STATUS           (0x06)
#define QMC5883_REG_TEMP_LSB         (0x07)
#define QMC5883_REG_TEMP_MSB         (0x08)
#define QMC5883_REG_CONFIG_1         (0x09)
#define QMC5883_REG_CONFIG_2         (0x0A)
#define QMC5883_REG_SET_RESET        (0x0B)

/* Mode Control */
#define QMC5883_MODE_SINGLE     0b00000000
#define QMC5883_MODE_CONTINOUS  0b00000001

/* Output Data Rate */
#define ODR_10Hz        0b00000000
#define ODR_50Hz        0b00000100
#define ODR_100Hz       0b00001000
#define ODR_200Hz       0b00001100
/* Full Scale */
#define RNG_2G          0b00000000
#define RNG_8G          0b00010000
/* Over Sample Ratio */
#define OSR_512         0b00000000
#define OSR_256         0b01000000
#define OSR_128         0b10000000
#define OSR_64          0b11000000

void qmc5883l_init(void);
void qmc5883l_write_reg(uint8_t reg, uint8_t val);
void qmc5883l_set_config(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr);
void qmc5883l_getrawdata(int16_t *mx, int16_t *my, int16_t *mz);
float qmc5883l_calc_heading(int16_t mx, int16_t my);

#endif /* QMC5883L_H_ */

