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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "KeyTask.h"

//����
void Key_Control(void);

void vTaskKey( void * pvParameters )
{
		uint32_t send_data1 = 1;
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		
		Key_Control();
		
		
		vTaskDelay( 1000 );
	}
	
}


//����-����-----------------------------------------------------------------------------
void  Key_Control(void)
{
	//�ϼ�������
	if(Key_PU.Key_RetVal == enKey_Click)
	{
		;
	}

	
}








