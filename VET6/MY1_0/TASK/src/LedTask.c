/**
  ******************************************************************************
  * @file    LedTask.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "LedTask.h"

void vTaskLed( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint8_t    r_queue;
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart,    /* 消息队列的句柄 */
                             (void *)&r_queue,      /* 发送的消息内容 */
                             xMaxBlockTime); /* 等待时间 一直等 */
		int i;
//		char *SendString;
//		if(pdTRUE == xReturn)
//		{
//      
//		
//				SendString = "接收Test_Queue消息队列成功!\r\n";
//				memcpy(SendBuff, SendString, 30);
//				Uart1_Start_DMA_Tx(sizeof(SendBuff));
//		}
//    else
//		{
//				SendString = "接收Test_Queue消息队列失败!\r\n";
//				memcpy(SendBuff, SendString, 30);
//				Uart1_Start_DMA_Tx(sizeof(SendBuff));
//		}
		bsp_Led_Flash(&LedA,i++);
//		bsp_Led_Flash(&LedB,10);
//		bsp_Led_Flash(&LedC,100);
		vTaskDelay( 100 );
	}
	
}





