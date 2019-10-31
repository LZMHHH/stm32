/**
  ******************************************************************************
  * @file    bsp_dwtdelay.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   mpu6050�ϲ��ļ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
	
#ifndef _bsp_DWT_DELAY_H_ 
#define _bsp_DWT_DELAY_H_ 

#include "includes.h"


// ����MCU���޸�
#define MY_MCU_SYSCLK           (72000000)  
 
void bsp_DWT_init(int sys_clk); // ΢����ʱ
void DwtDelay_uS(int uSec); 

#define DwtDelay_mS(mSec)    DwtDelay_uS( mSec*1000 ) 

#endif


