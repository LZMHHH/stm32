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

/* �Ƿ��ӡ������Ϣ */
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


// �û�������ͷ�ļ�
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


//����ʵ��
#include "LedTask.h"
#include "KeyTask.h"
#include "CommunicateTask.h"
#if IFPRINTTASK
#include "CpuTask.h"
#endif


//����ר��
/* ���������е��� */
extern void vSetupSysInfoTest(void);

//��Ϣ�㲥
extern TaskHandle_t xQueue_uart1Rx;  //uart1�Ľ�����Ϣ����
extern TaskHandle_t xQueue_uart1Tx;  //uart1�ķ�����Ϣ����

/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif


