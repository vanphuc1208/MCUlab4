/*
 * fsm.h
 *
 *  Created on: Nov 10, 2023
 *      Author: OS
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_
#include "main.h"
#include "software_timer.h"
#include "string.h"

#define MAX_BUFFER_SIZE  30
extern uint8_t temp ;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer ;
extern uint8_t buffer_flag;
extern ADC_HandleTypeDef hadc1 ;

extern UART_HandleTypeDef huart2 ;

void command_parser_fsm();

void uart_communication_fsm();
#endif /* INC_FSM_H_ */
