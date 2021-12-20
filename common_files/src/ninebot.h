/****************************************************************************/
//  Function: Header file ninebot communication
//  Author:   Camilo Ruiz
//  Date:    october 10 2017
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
// I am not responsible of any damage caused by the misuse of this library
// use at your own risk
//
// If you modify this or use this, please don't delete my name and give me the credits
// Greetings from Colombia :) 
// Hardware port by ub4raf
/****************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//#include "mbed.h"
#define NinebotHeader0 0x55//0x55
#define NinebotHeader1 0xAA//0xAA
#define Ninebotread 0x01
#define Ninebotwrite 0x03
#define NinebotMaxPayload 0x38
//message len max is 256, header, command, rw and cheksum total len is 8, therefore payload max len is 248
//max input bluetooth buffer in this chip allows a payload max 0x38
typedef struct {
	uint8_t start1;
	uint8_t start2;
	uint8_t len;
	uint8_t addr;
	uint8_t cmd;
    uint8_t arg;
    uint8_t payload[NinebotMaxPayload];
    uint8_t CheckSum[2];
} NinebotPack;
                                   //0     1    2     3      4    5     6      7     8    9     10    11    12    13
//static uint8_t	ui8_tx_buffer[] = {0x55, 0xAA, 0x08, 0x21, 0x64, 0x00, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*
ui8_tx_buffer[10]=MS->Speed;
			ui8_tx_buffer[6]=MS->gear_state;
			ui8_tx_buffer[7]=map(MS->Voltage,33000,42000,0,96);
			if(MS->light)ui8_tx_buffer[8]=64;
			else ui8_tx_buffer[8]=0;
			addCRC((uint8_t*)ui8_tx_buffer, ui8_tx_buffer[2]+6);
			HAL_HalfDuplex_EnableTransmitter(&huart1);
			HAL_UART_Transmit_DMA(&huart1, (uint8_t*)ui8_tx_buffer, sizeof(ui8_tx_buffer));
			}
*/

enum m365_display_mode{
	M365_MODE_SLOW=3,
	M365_MODE_DRIVE=1,
	M365_MODE_SPORT=4,
};

typedef struct {
	uint8_t start1;  	//0
	uint8_t start2;  	//1
	uint8_t len;		//2
	uint8_t addr;		//3
	uint8_t cmd;		//4
    uint8_t arg;		//5
    uint8_t mode; 		//6
	uint8_t battery;	//7
	uint8_t light;		//8
	uint8_t beep;		//9
	uint8_t speed;		//10
	uint8_t data11;		//11
    uint8_t CheckSum[2];//12-13
} m365Answer;


void addCRC(uint8_t * message, uint8_t size);


uint8_t ninebot_parse(uint8_t data, NinebotPack *message);