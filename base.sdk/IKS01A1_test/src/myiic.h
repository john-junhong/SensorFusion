/*
 * myiic.h
 *
 *  Created on: 2016��11��1��
 *      Author: mengxian
 */

#ifndef SRC_MYIIC_H_
#define SRC_MYIIC_H_

#include "xil_types.h"
#include "i2c.h"

void i2c_init();
void i2c_write_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 regData);
u8 i2c_read_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 bytes);

#endif /* SRC_MYIIC_H_ */
