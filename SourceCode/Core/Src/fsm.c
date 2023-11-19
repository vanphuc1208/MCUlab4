/*
 * fsm.c
 *
 *  Created on: Nov 10, 2023
 *      Author: OS
 */

#include "fsm.h"
#define MAX_BUFFER_SIZE  30
uint8_t temp ;
uint8_t checkString[MAX_BUFFER_SIZE]="";
uint8_t buffer_flag = 0;
uint32_t ADC_value=0;
#define Startcmd 0
#define Readcmd  1
#define Checkcmd 2

#define RST 3
#define OK  4
int status=Startcmd;
int cmd_flag=10;
void command_parser_fsm() {
switch (status) {
	case Startcmd:
		if(temp=='!') {
			status=Readcmd;
			memset(checkString,0,sizeof(checkString));
		}
		break;
	case Readcmd:
		if(temp=='!') {
			memset(checkString,0,sizeof(checkString));
		}
		else if (temp=='#') {
			if(strcmp(checkString,"RST")==0) {
				cmd_flag=RST;
				setTimer1(1);
			}
			if(strcmp(checkString,"OK")==0) cmd_flag=10;
		}
		else {
			 strcat(checkString, (char*)&temp);
		}
		break;
	default:
		break;
}
}

void uart_communication_fsm()
{
	char str[100];
	switch(cmd_flag)
	{
		case RST:
			if(timer1_flag == 1)
			{
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%d#\r\n",ADC_value), 1000);
				status=Startcmd;
				setTimer1(300);
			}
			break;
		default:
			break;
	}
}
