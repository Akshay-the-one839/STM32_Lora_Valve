#ifndef LORA_UART_H
#define LORA_UART_H

#include "cmsis_os.h"
#include "usart.h"

void Lora_UART_Init(void);
void Lora_UART_StartReceive(void);

extern QueueHandle_t loraRxQueue;

#endif