/*
 ******************************************************************************************
 * @file      main.c
 * @author    GowinSemiconductor
 * @device    Gowin_EMPU(GW1NS-4C)
 * @brief     Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>

/* Declarations ------------------------------------------------------------------*/
void UartInit(void);
void TimerInit(TIMER_TypeDef* TIMERx);

/* Definitions ------------------------------------------------------------------*/
volatile uint32_t counter;

/* Functions ------------------------------------------------------------------*/
int main()
{   
  int num=0;
	
	NVIC_InitTypeDef InitTypeDef_NVIC;//Interrupt handler
	
	SystemInit();	//Initializes system
  UartInit();		//Initializes UART0
	
  printf("\nUart Initial finished\r\n");
  printf("\nTimer Initial:\r\n");
	
  TimerInit(TIMER0);	//Initializes Timer0
	
  counter=0;//Dispaly the message
	
	//Timer0 interrupt handler
	InitTypeDef_NVIC.NVIC_IRQChannel = TIMER0_IRQn;
  InitTypeDef_NVIC.NVIC_IRQChannelPreemptionPriority = 1;
  InitTypeDef_NVIC.NVIC_IRQChannelSubPriority = 1;
  InitTypeDef_NVIC.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&InitTypeDef_NVIC);

  printf("\nNVIC ENABLE IRQ TIMER0\r\n");
  TIMER_EnableIRQ(TIMER0);
  printf("\nTIMER0 IRQ ENABLE\r\n");
  TIMER_StartTimer(TIMER0);
  printf("\nSTART TIMER0\r\n");
	
  while(1)
  {
     if(counter==2)
     {
       counter=0;
			 
       printf("\r\n");
			 printf("count number: %d ",num);
			 
       num++;
     }
		
     if(num==60)
		 {	
       num=0;
		}
  }
}

//Initializes UART0
void UartInit(void)
{
  UART_InitTypeDef UART_InitStruct;
	
  UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
  UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
  UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
  UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
  UART_InitStruct.UART_Hstm = DISABLE;
  UART_InitStruct.UART_BaudRate = 115200;//Baud Rate
	
  UART_Init(UART0,&UART_InitStruct);
}

//Initializes Timer0
void TimerInit(TIMER_TypeDef* TIMERx)
{ 
  TIMERx->INTCLEAR = 0;
  TIMER0->RELOAD=25000026;//Set the value of the Timmer 1s
  TIMER0->VALUE= TIMER0->RELOAD; //Set the init value
  TIMER0->CTRL=0;  // timmer interrupt
	
  printf("TIMERx->INTCLEAR = 0;\r\n");
  printf("TIMER0->RELOAD=25000026;\r\n");
  printf("TIMERx->VALUE= TIMER0->RELOAD;\r\n");
  printf("TIMERx->CTRL = 0;\r\n");
}

//Timer0 interrupt handler
void TIMER0_Handler(void)
{
  if(TIMER_GetIRQStatus(TIMER0) != RESET)
  {
    counter++;
    TIMER_ClearIRQ(TIMER0);
  }
}
