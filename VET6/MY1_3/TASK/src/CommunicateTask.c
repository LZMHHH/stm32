/**
  ******************************************************************************
  * @file    CommunicateTask.c
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
#include "CommunicateTask.h"


//Uart1的接收任务
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint8_t    ReadBuff[DEBUG1_RX_BSIZE];  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* 消息队列的句柄 */
                             (void *)&ReadBuff,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		//接收成功后马上发回去
		xReturn = xQueueSend( xQueue_uart1Tx,  /* 消息队列的句柄 */
													&ReadBuff,       /* 发送的消息内容 */
													0 );             /* 等待时间 0 */													
		
	}
}

//Uart1的发送任务
void vTaskUart1Tx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint8_t    ReadBuff[DEBUG1_TX_BSIZE];  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);

	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             (void *)&ReadBuff,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
														 
//		Uart1_DMA_SendString("接收Test_Queue消息队列成功!\r",
//													-1);	
														 
		Uart1_DMA_SendString((char *)ReadBuff,
													-1);	

																		
		
	}
}


