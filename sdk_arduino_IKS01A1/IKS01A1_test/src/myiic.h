/*
 * myiic.h
 *
 *  Created on: 2016��11��1��
 *      Author: mengxian
 */

#ifndef SRC_MYIIC_H_
#define SRC_MYIIC_H_

#include "arduino.h"

void iic_write_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 regData);
u8 iic_read_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 bytes);

#endif /* SRC_MYIIC_H_ */
