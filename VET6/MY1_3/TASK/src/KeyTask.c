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

//声明
void Key_Control(void);

void vTaskKey( void * pvParameters )
{
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		
		Key_Control();
		
		
		vTaskDelay( 1000 );
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








