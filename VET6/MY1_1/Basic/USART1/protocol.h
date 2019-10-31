/**
  ******************************************************************************
  * @file    usart3.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   这里使用接收中断.
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __PROTOCOL_H
#define	__PROTOCOL_H


#include "includes.h" 



/*上报状态枚举*/
typedef enum
{
  State_ReTno = 0,  //       数据传送空闲  (也可以说处理完毕的回归)
	State_ReTing,     //       数据编码完毕,进入发送状态
	State_ReTed,      //       发送函数已经执行
}State_ReData;




void Protocol3(void);
void ProtocolCpyData3(void);
u8   Reported_Data3(void);
char Free3_SendString(const char *pSrc, u8 pSite);
void Free3_Send_Con(void);
char Free3_SendNum(const char *pSrc,long int pnum, u8 pSite);
void save_FlashData(u8 k);

void ProtocolCpyData3sem(void);
#endif /* __USART_H */
