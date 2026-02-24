#include "lora_uart.h"
#include "main.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "queue.h"

QueueHandle_t loraRxQueue;

static uint8_t rxByte;

void Lora_UART_Init(void)
{
    loraRxQueue = xQueueCreate(128, sizeof(uint8_t));
}

void Lora_UART_StartReceive(void)
{
    HAL_UART_Receive_IT(&huart1, &rxByte, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (huart->Instance == USART1)
    {
        xQueueSendFromISR(loraRxQueue, &rxByte, &xHigherPriorityTaskWoken);
        HAL_UART_Receive_IT(&huart1, &rxByte, 1);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    
}