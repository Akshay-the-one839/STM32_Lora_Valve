#include "command_parser.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Valve pins
#define V1_GPIO_Port GPIOA
#define V1_Pin GPIO_PIN_0
#define V2_GPIO_Port GPIOA
#define V2_Pin GPIO_PIN_1
#define V3_GPIO_Port GPIOA
#define V3_Pin GPIO_PIN_2
#define V4_GPIO_Port GPIOA
#define V4_Pin GPIO_PIN_3
#define V5_GPIO_Port GPIOA
#define V5_Pin GPIO_PIN_4
#define V6_GPIO_Port GPIOA
#define V6_Pin GPIO_PIN_5
#define V7_GPIO_Port GPIOA
#define V7_Pin GPIO_PIN_6
#define V8_GPIO_Port GPIOA
#define V8_Pin GPIO_PIN_7

#define SIGLED_GPIO_Port GPIOC
#define SIGLED_Pin GPIO_PIN_13

// States and flags
char state1 = '0';
char state2 = '0';
char state3 = '0';
char state4 = '0';
char state5 = '0';
char state6 = '0';
char state7 = '0';
char state8 = '0';

int vanoflg1 = 0;
int vanoflg2 = 0;
int vanoflg3 = 0;
int vanoflg4 = 0;
int vanoflg5 = 0;
int vanoflg6 = 0;
int vanoflg7 = 0;
int vanoflg8 = 0;

int txflg = 0;

void ProcessCommand(char *cmd)
{
    int Index = 0;
    char vno1 = cmd[Index]; Index++; Index++; // skip *
    state1 = cmd[Index]; Index++; Index++;
    char vno2 = cmd[Index]; Index++; Index++;
    state2 = cmd[Index]; Index++; Index++;
    char vno3 = cmd[Index]; Index++; Index++;
    state3 = cmd[Index]; Index++; Index++;
    char vno4 = cmd[Index]; Index++; Index++;
    state4 = cmd[Index]; Index++; Index++;
    char vno5 = cmd[Index]; Index++; Index++;
    state5 = cmd[Index]; Index++; Index++;
    char vno6 = cmd[Index]; Index++; Index++;
    state6 = cmd[Index]; Index++; Index++;
    char vno7 = cmd[Index]; Index++; Index++;
    state7 = cmd[Index]; Index++; Index++;
    char vno8 = cmd[Index]; Index++; Index++;
    state8 = cmd[Index]; Index++; Index++;
    // BW ignored

    // V1
    if(vno1 == '1' && vanoflg1 == 0 && state1 == '1')
    {
        HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, GPIO_PIN_SET);
        vanoflg1 = 1;
    }
    if(vno1 == '1' && vanoflg1 == 1 && state1 == '0')
    {
        HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, GPIO_PIN_RESET);
        vanoflg1 = 0;
    }
    // V2
    if(vno2 == '2' && vanoflg2 == 0 && state2 == '1')
    {
        HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, GPIO_PIN_SET);
        vanoflg2 = 1;
    }
    if(vno2 == '2' && vanoflg2 == 1 && state2 == '0')
    {
        HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, GPIO_PIN_RESET);
        vanoflg2 = 0;
    }
    // V3
    if(vno3 == '3' && vanoflg3 == 0 && state3 == '1')
    {
        HAL_GPIO_WritePin(V3_GPIO_Port, V3_Pin, GPIO_PIN_SET);
        vanoflg3 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno3 == '3' && vanoflg3 == 1 && state3 == '0')
    {
        HAL_GPIO_WritePin(V3_GPIO_Port, V3_Pin, GPIO_PIN_RESET);
        vanoflg3 = 0;
    }
    // V4
    if(vno4 == '4' && vanoflg4 == 0 && state4 == '1')
    {
        HAL_GPIO_WritePin(V4_GPIO_Port, V4_Pin, GPIO_PIN_SET);
        vanoflg4 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno4 == '4' && vanoflg4 == 1 && state4 == '0')
    {
        HAL_GPIO_WritePin(V4_GPIO_Port, V4_Pin, GPIO_PIN_RESET);
        vanoflg4 = 0;
    }
    // V5
    if(vno5 == '5' && vanoflg5 == 0 && state5 == '1')
    {
        HAL_GPIO_WritePin(V5_GPIO_Port, V5_Pin, GPIO_PIN_SET);
        vanoflg5 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno5 == '5' && vanoflg5 == 1 && state5 == '0')
    {
        HAL_GPIO_WritePin(V5_GPIO_Port, V5_Pin, GPIO_PIN_RESET);
        vanoflg5 = 0;
    }
    // V6
    if(vno6 == '6' && vanoflg6 == 0 && state6 == '1')
    {
        HAL_GPIO_WritePin(V6_GPIO_Port, V6_Pin, GPIO_PIN_SET);
        vanoflg6 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno6 == '6' && vanoflg6 == 1 && state6 == '0')
    {
        HAL_GPIO_WritePin(V6_GPIO_Port, V6_Pin, GPIO_PIN_RESET);
        vanoflg6 = 0;
    }
    // V7
    if(vno7 == '7' && vanoflg7 == 0 && state7 == '1')
    {
        HAL_GPIO_WritePin(V7_GPIO_Port, V7_Pin, GPIO_PIN_SET);
        vanoflg7 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno7 == '7' && vanoflg7 == 1 && state7 == '0')
    {
        HAL_GPIO_WritePin(V7_GPIO_Port, V7_Pin, GPIO_PIN_RESET);
        vanoflg7 = 0;
    }
    // V8
    if(vno8 == '8' && vanoflg8 == 0 && state8 == '1')
    {
        HAL_GPIO_WritePin(V8_GPIO_Port, V8_Pin, GPIO_PIN_SET);
        vanoflg8 = 1;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if(vno8 == '8' && vanoflg8 == 1 && state8 == '0')
    {
        HAL_GPIO_WritePin(V8_GPIO_Port, V8_Pin, GPIO_PIN_RESET);
        vanoflg8 = 0;
    }
}

void txvalve()
{
    HAL_GPIO_WritePin(SIGLED_GPIO_Port, SIGLED_Pin, GPIO_PIN_SET);
    for(int i2 = 0; i2 < 5; i2++)
    {
        char buffer[100];
        sprintf(buffer, "$A,1,%c,2,%c,3,%c,4,%c,5,%c,6,%c,7,%c,8,%c,", state1, state2, state3, state4, state5, state6, state7, state8);
        HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    HAL_GPIO_WritePin(SIGLED_GPIO_Port, SIGLED_Pin, GPIO_PIN_RESET);
}