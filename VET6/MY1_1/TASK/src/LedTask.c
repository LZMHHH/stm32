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
	
	while(1)
	{


		bsp_Led_Flash(&LedA,1);
		bsp_Led_Flash(&LedB,10);
		bsp_Led_Flash(&LedC,100);
		vTaskDelay( 100 );
	}
	
}





