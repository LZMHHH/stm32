/**
  ******************************************************************************
  * @file    CpuTask.c
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
#include "CpuTask.h"

void vTaskCpu( void * pvParameters )
{
	
		uint8_t    pcWriteBuffer[500];		//������������ʱ����Ϣ

		BaseType_t xReturn = pdTRUE;    /* ����һ������ֵ��Ĭ��ΪpdTRUE */
  	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
		while (1)
		 {
			  Usar1_SendString(DEBUG1_USARTx,"=================================================\r\n");	
				Usar1_SendString(DEBUG1_USARTx,"������      ����״̬ ���ȼ�   ʣ��ջ �������\r\n");	
				vTaskList((char *)&pcWriteBuffer);			 
				Usar1_SendString(DEBUG1_USARTx,(char *)pcWriteBuffer);
			  Usar1_SendString(DEBUG1_USARTx,"\r\n������       ���м���         ʹ����\r\n");	
			  vTaskGetRunTimeStats((char *)&pcWriteBuffer);
			  Usar1_SendString(DEBUG1_USARTx,(char *)pcWriteBuffer);		
				Usar1_SendString(DEBUG1_USARTx,"\r\n");	

				vTaskDelay(1000);   /* ��ʱ500��tick */		
		 }

}





