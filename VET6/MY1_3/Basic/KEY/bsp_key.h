/**
  ******************************************************************************
  * @file    key.h
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
#ifndef __KEY_H
#define __KEY_H	 
#include "includes.h"



#define ON  1
#define OFF 0
					


/* 按键返回状态 0未按 1按下 */
#define NO_KEY          (0x00)
#define KEY_SINGLE      (0x01)

//别名
typedef  struct  class_key         CLASS_Key;

/* 扫描状态机表 */
typedef enum
{
    enKEYx_Leisure,          /*空闲态 */
    enKEYx_Debounce,      /*确认与消抖态 */
    enKEYx_Confirm,       /*确认按键状态*/
}KEY_ScanStatus;

/* 设备机表 */
typedef enum
{
	  enKey_NO,          
    enKey_PU,       
    enKey_PD,
    enKey_PL,
    enKey_PR,	
	  enKey_PM,	
	  enKey_PT,	
}KEYx_Status;		
/* 类型状态机表 */
typedef enum
{
	enKey_No,           //没有按下
	enKey_Click,        //单击
	enKey_LongPress,    //长按
}KEY_RetStatus;

//引脚配置
typedef struct class_key_config
{
	uint32_t      gpio_clk;
	GPIO_TypeDef* gpio_port;
	uint32_t      gpio_pin;
}CLASS_key_config;

//按键类
struct class_key 
{
	u8                 key_name;       //按键名字，枚举
	KEY_ScanStatus     Status_Scan;    //扫描状态
	KEY_RetStatus      Key_RetVal;     //返回类型
	u16                Time_Press;     //时间值（次数）
	u8                 Flag_IfDataed;  //是否被处理过标志位
	u8                 Flag_AddDir;    //区分按压次数心跳
	
	CLASS_key_config   config;         //引脚配置
};




//广播
extern u8 KEY_RetValue;
//创建按键
extern CLASS_Key   Key_PU;     //上
extern CLASS_Key   Key_PD;     //下
extern CLASS_Key   Key_PL;     //左
extern CLASS_Key   Key_PR;     //右
extern CLASS_Key   Key_PM;     //中

#define Key_Pre( CLASS_Key )	       GPIO_ReadInputDataBit((CLASS_Key)->config.gpio_port,(CLASS_Key)->config.gpio_pin) 

void   bsp_KEY_Init      (void);          //按键初始化
void   Key_Scan(CLASS_Key* key_x);

#endif 
