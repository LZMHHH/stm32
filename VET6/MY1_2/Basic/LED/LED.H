/**
  ******************************************************************************
  * @file    x
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __BSP_LED_H_

#define __BSP_LED_H_

#include "includes.h"  //因为main.c有调用过，如果这文件也调用了就不必再调用了



//#define OFF  1
//#define ON   0



/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

/* 设备机表 */
typedef enum
{
	LED_A,              //红
	LED_B,              //蓝
	LED_C,              //黄
	FMQ,                //蜂鸣器
}LEDN_Status;

//LED配置参数
typedef struct class_led_config
{
	uint32_t      gpio_clk;
	GPIO_TypeDef* gpio_port;
	uint32_t      gpio_pin;
}CLASS_led_config;

//led类
struct class_led 
{
	u8         led_name;
	u8         flag_kg;        //led开关
	int        cycle;          //led周期
	int        temp;           //辅助频率计算
	
	//dev配置
	CLASS_led_config config;
	
};

//别名
typedef  struct  class_led     CLASS_Led;




//广播
extern CLASS_Led   LedA;
extern CLASS_Led   LedB;
extern CLASS_Led   LedC;
extern CLASS_Led   Fmq;





void   bsp_LED_Init      (void);  //初始化
void   bsp_Led_Flash    (CLASS_Led* led_n,int time);
#endif


