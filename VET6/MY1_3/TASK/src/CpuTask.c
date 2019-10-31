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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "CpuTask.h"

#if IFPRINTTASK
void vTaskCpu( void * pvParameters )
{
	
		uint8_t    pcWriteBuffer[500];		//保存任务运行时间信息

		BaseType_t xReturn = pdTRUE;    /* 定义一个返回值，默认为pdTRUE */
  	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
		while (1)
		 {
			  Usar1_SendString(DEBUG1_USARTx,"=================================================\r\n");	
				Usar1_SendString(DEBUG1_USARTx,"任务名      任务状态 优先级   剩余栈 任务序号\r\n");	
				vTaskList((char *)&pcWriteBuffer);			 
				Usar1_SendString(DEBUG1_USARTx,(char *)pcWriteBuffer);
			  Usar1_SendString(DEBUG1_USARTx,"\r\n任务名       运行计数         使用率\r\n");	
			  vTaskGetRunTimeStats((char *)&pcWriteBuffer);
			  Usar1_SendString(DEBUG1_USARTx,(char *)pcWriteBuffer);		
				Usar1_SendString(DEBUG1_USARTx,"\r\n");	

				vTaskDelay(1000);   /* 延时500个tick */		
		 }

}

#endif



