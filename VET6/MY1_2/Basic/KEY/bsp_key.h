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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __KEY_H
#define __KEY_H	 
#include "includes.h"



#define ON  1
#define OFF 0
					


/* ��������״̬ 0δ�� 1���� */
#define NO_KEY          (0x00)
#define KEY_SINGLE      (0x01)

//����
typedef  struct  class_key         CLASS_Key;

/* ɨ��״̬���� */
typedef enum
{
    enKEYx_Leisure,          /*����̬ */
    enKEYx_Debounce,      /*ȷ��������̬ */
    enKEYx_Confirm,       /*ȷ�ϰ���״̬*/
}KEY_ScanStatus;

/* �豸���� */
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
/* ����״̬���� */
typedef enum
{
	enKey_No,           //û�а���
	enKey_Click,        //����
	enKey_LongPress,    //����
}KEY_RetStatus;

//��������
typedef struct class_key_config
{
	uint32_t      gpio_clk;
	GPIO_TypeDef* gpio_port;
	uint32_t      gpio_pin;
}CLASS_key_config;

//������
struct class_key 
{
	u8                 key_name;       //�������֣�ö��
	KEY_ScanStatus     Status_Scan;    //ɨ��״̬
	KEY_RetStatus      Key_RetVal;     //��������
	u16                Time_Press;     //ʱ��ֵ��������
	u8                 Flag_IfDataed;  //�Ƿ񱻴������־λ
	u8                 Flag_AddDir;    //���ְ�ѹ��������
	
	CLASS_key_config   config;         //��������
};




//�㲥
extern u8 KEY_RetValue;
//��������
extern CLASS_Key   Key_PU;     //��
extern CLASS_Key   Key_PD;     //��
extern CLASS_Key   Key_PL;     //��
extern CLASS_Key   Key_PR;     //��
extern CLASS_Key   Key_PM;     //��

#define Key_Pre( CLASS_Key )	       GPIO_ReadInputDataBit((CLASS_Key)->config.gpio_port,(CLASS_Key)->config.gpio_pin) 

void   bsp_KEY_Init      (void);          //������ʼ��
void   Key_Scan(CLASS_Key* key_x);

#endif 
