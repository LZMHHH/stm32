/**
  ******************************************************************************
  * @file    bsp_dwtdelay.h
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
	
#ifndef _bsp_DWT_DELAY_H_ 
#define _bsp_DWT_DELAY_H_ 

#include "includes.h"


// 根据MCU做修改
#define MY_MCU_SYSCLK           (72000000)  
 
void bsp_DWT_init(int sys_clk); // 微秒延时
void DwtDelay_uS(int uSec); 

#define DwtDelay_mS(mSec)    DwtDelay_uS( mSec*1000 ) 

#endif


