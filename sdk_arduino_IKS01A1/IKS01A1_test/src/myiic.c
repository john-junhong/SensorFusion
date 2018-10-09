/*
 * myiic.c
 *
 *  Created on: 2016��11��1��
 *      Author: mengxian
 */
#include "myiic.h"

void iic_write_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 regData){
	u8 data_buffer[2];
	data_buffer[0] = regAddr;
	data_buffer[1] = regData & 0xff;
	iic_write(XPAR_IIC_0_BASEADDR, dev7bitAddr, data_buffer, 2);
}

u8 iic_read_IKS01A1(u8 dev7bitAddr, u8 regAddr, u8 bytes){
	u8 data_buffer[2];
	u32 resultData;
	data_buffer[0] = regAddr;
	iic_write(XPAR_IIC_0_BASEADDR, dev7bitAddr, data_buffer, 1);
	iic_read(XPAR_IIC_0_BASEADDR, dev7bitAddr,  data_buffer, bytes);
	if(bytes == 1){
		resultData = data_buffer[0];
	}
	else{
		resultData = (data_buffer[0] & 0xff)<<8 | (data_buffer[1] & 0xff);
	}
	return resultData;
}
