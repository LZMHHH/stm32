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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "LedTask.h"

void vTaskLed( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    r_queue;
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart,    /* ��Ϣ���еľ�� */
                             (void *)&r_queue,      /* ���͵���Ϣ���� */
                             xMaxBlockTime); /* �ȴ�ʱ�� һֱ�� */
		int i;
//		char *SendString;
//		if(pdTRUE == xReturn)
//		{
//      
//		
//				SendString = "����Test_Queue��Ϣ���гɹ�!\r\n";
//				memcpy(SendBuff, SendString, 30);
//				Uart1_Start_DMA_Tx(sizeof(SendBuff));
//		}
//    else
//		{
//				SendString = "����Test_Queue��Ϣ����ʧ��!\r\n";
//				memcpy(SendBuff, SendString, 30);
//				Uart1_Start_DMA_Tx(sizeof(SendBuff));
//		}
		bsp_Led_Flash(&LedA,i++);
//		bsp_Led_Flash(&LedB,10);
//		bsp_Led_Flash(&LedC,100);
		vTaskDelay( 100 );
	}
	
}





