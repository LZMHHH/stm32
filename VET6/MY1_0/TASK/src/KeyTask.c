/**
  ******************************************************************************
  * @file    KeyTask.c
  * @author  fire
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
#include "KeyTask.h"

void  Key_Control(void);

void vTaskKey( void * pvParameters )
{
		uint32_t send_data1 = 1;
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		
		Key_Control();
		
		xQueueSend( xQueue_uart, /* 消息队列的句柄 */
                            &send_data1,/* 发送的消息内容 */
                            0 );        /* 等待时间 0 */
		
		vTaskDelay( 10 );
	}
	
}


//按键-处理-----------------------------------------------------------------------------
void  Key_Control(void)
{
	//上键被单击
	if(Key_PU.Key_RetVal == enKey_Click)
	{
		;
	}

	
}








