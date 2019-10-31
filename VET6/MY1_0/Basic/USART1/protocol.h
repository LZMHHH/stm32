/**
  ******************************************************************************
  * @file    usart3.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   ����ʹ�ý����ж�.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __PROTOCOL_H
#define	__PROTOCOL_H


#include "includes.h" 



/*�ϱ�״̬ö��*/
typedef enum
{
  State_ReTno = 0,  //       ���ݴ��Ϳ���  (Ҳ����˵������ϵĻع�)
	State_ReTing,     //       ���ݱ������,���뷢��״̬
	State_ReTed,      //       ���ͺ����Ѿ�ִ��
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
