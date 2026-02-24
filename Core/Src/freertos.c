/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include "lora_uart.h"
#include "command_parser.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId valveTaskHandle;
osThreadId parserTaskHandle;

#define SIGLED_GPIO_Port GPIOC
#define SIGLED_Pin GPIO_PIN_13
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void StartValveTask(void const * argument);
void StartParserTask(void const * argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  Lora_UART_Init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */


  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadDef(valveTask, StartValveTask, osPriorityLow, 0, 256);
valveTaskHandle = osThreadCreate(osThread(valveTask), NULL);

osThreadDef(parserTask, StartParserTask, osPriorityNormal, 0, 512);
parserTaskHandle = osThreadCreate(osThread(parserTask), NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void StartValveTask(void const * argument)
{
  Lora_UART_StartReceive();
  for(;;)
  {
    HAL_GPIO_WritePin(SIGLED_GPIO_Port, SIGLED_Pin, GPIO_PIN_RESET);
    if(txflg)
    {
      txvalve();
      txflg = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
void StartParserTask(void const * argument)
{
    uint8_t rxByte;
    char commandBuffer[35]; // 34 + null
    uint8_t index = 0;
    int expectingCommand = 0;

    for(;;)
    {
        if (xQueueReceive(loraRxQueue, &rxByte, portMAX_DELAY) == pdTRUE)
        {
            if (rxByte == 'A')
            {
                index = 0;
                expectingCommand = 1;
            }
            else if (rxByte == 'a')
            {
                txflg = 1;
            }
            else if (expectingCommand)
            {
                commandBuffer[index++] = rxByte;
                if (index == 34)
                {
                    commandBuffer[index] = '\0';
                    ProcessCommand(commandBuffer);
                    expectingCommand = 0;
                }
            }
        }
    }
}
/* USER CODE END Application */

