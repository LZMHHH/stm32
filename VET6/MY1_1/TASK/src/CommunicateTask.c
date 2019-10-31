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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "CommunicateTask.h"


#if DEBUG1_SAFETY

//Uart1�Ľ�������
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    ReadBuff[DEBUG1_RX_BSIZE];  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		//���ճɹ������Ϸ���ȥ
		xReturn = xQueueSend( xQueue_uart1Tx,  /* ��Ϣ���еľ�� */
													&ReadBuff,       /* ���͵���Ϣ���� */
													0 );             /* �ȴ�ʱ�� 0 */													
		
	}
}

//Uart1�ķ�������
void vTaskUart1Tx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    ReadBuff[DEBUG1_TX_BSIZE];  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);

	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
										
														 
//		Uart1_DMA_SendString("����Test_Queue��Ϣ���гɹ�!\r",
//													-1);	
														 
		Uart1_DMA_SendString((char *)ReadBuff,
													-1);	

																		
		
	}
}

#else

//Uart1�Ľ�������
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    *ReadBuff;  /* ����ָ�� */
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		//���ճɹ������Ϸ���ȥ
		xReturn = xQueueSend( xQueue_uart1Tx,  /* ��Ϣ���еľ�� */
													&ReadBuff,       /* ���͵���Ϣ���� */
													0 );             /* �ȴ�ʱ�� 0 */													
		
	}
}

//Uart1�ķ�������
void vTaskUart1Tx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    *ReadBuff;  /* ����ָ�� */
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);

	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
										
														 
//		Uart1_DMA_SendString("����Test_Queue��Ϣ���гɹ�!\r",
//													-1);	
														 
		Uart1_DMA_SendString((char *)ReadBuff,
													-1);	

																		
		
	}
}


#endif
