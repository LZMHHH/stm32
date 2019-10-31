/**
  ******************************************************************************
  * @file    bsp_systick.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   mpu6050上层文件
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
	
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  

void SysTick_Init(u8 SYSCLK);    //   SYSCLK  M
void SysTick_Delay_ms(u16 nms);
void SysTick_Delay_us(u32 nus);

#endif


