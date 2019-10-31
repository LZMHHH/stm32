/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include <stdarg.h>
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

/* 是否打印任务信息 */
#define IFPRINTTASK  false


/*
*********************************************************************************************************
*                                              p
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*
*********************************************************************************************************
*                                                 ST
*********************************************************************************************************
*/

#include  "stm32f10x.h"


// 用户开发的头文件
#include "bsp.h"
#include "control.h"
#include "bsp_dwt_delay.h"
#include "delay.h"
#include "led.h"
#include "config_param.h"
#include "bsp_key.h"
#include "usart1.h"
#if IFPRINTTASK
#include "bsp_tim_pwm.h"
#endif


//任务实体
#include "LedTask.h"
#include "KeyTask.h"
#include "CommunicateTask.h"
#if IFPRINTTASK
#include "CpuTask.h"
#endif


//调试专用
/* 在主函数中调用 */
extern void vSetupSysInfoTest(void);

//消息广播
extern TaskHandle_t xQueue_uart1Rx;  //uart1的接收消息队列
extern TaskHandle_t xQueue_uart1Tx;  //uart1的发送消息队列

/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif


