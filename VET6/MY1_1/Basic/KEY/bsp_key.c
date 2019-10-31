/**
  ******************************************************************************
  * @file    key.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
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
#include "bsp_key.h"

/* ��������ֵ */
u8 KEY_RetValue;

//�������� + ����
CLASS_Key   Key_PU={.key_name         = enKey_PU,
										.config.gpio_clk  = RCC_APB2Periph_GPIOA,
										.config.gpio_port = GPIOA,
										.config.gpio_pin  = GPIO_Pin_0
										};     //��
CLASS_Key   Key_PD={.key_name         = enKey_PD,
										.config.gpio_clk  = RCC_APB2Periph_GPIOC,
										.config.gpio_port = GPIOC,
										.config.gpio_pin  = GPIO_Pin_13
										};     //��
//CLASS_Key   Key_PL={.key_name         = enKey_PL,
//										.config.gpio_clk  = RCC_APB2Periph_GPIOB,
//										.config.gpio_port = GPIOB,
//										.config.gpio_pin  = gpio_pin_8
//										};     //��
//CLASS_Key   Key_PR={.key_name         = enKey_PR,
//										.config.gpio_clk  = RCC_APB2Periph_GPIOC,
//										.config.gpio_port = GPIOC,
//										.config.gpio_pin  = gpio_pin_13
//										};     //��
//CLASS_Key   Key_PM={.key_name         = enKey_PM,
//										.config.gpio_clk  = RCC_APB2Periph_GPIOC,
//										.config.gpio_port = GPIOC,
//										.config.gpio_pin  = gpio_pin_14
//										};     //��


/**************************************************************************
�������ܣ������������ų�ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
static void key_config(CLASS_Key *key_n)
{
	GPIO_InitTypeDef    KEY_GPIO_IniStruct;
	
	RCC_APB2PeriphClockCmd(key_n->config.gpio_clk, ENABLE);	
	KEY_GPIO_IniStruct.GPIO_Pin  = key_n->config.gpio_pin;
	KEY_GPIO_IniStruct.GPIO_Mode = GPIO_Mode_IPD;   //��������
	GPIO_Init(key_n->config.gpio_port,&KEY_GPIO_IniStruct);
}
										
										
/**************************************************************************
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void bsp_KEY_Init(void)
{
	key_config(&Key_PU);
	key_config(&Key_PD);
//	key_config(&Key_PL);
//	key_config(&Key_PR);
//	key_config(&Key_PM);

} 


/* ����ɨ����� */
void Key_Scan(CLASS_Key* key_x)
{	
			key_x->Time_Press++;        //ʱ��ֵ����
			switch(key_x->Status_Scan)
			{
					case enKEYx_Leisure:
							if(Key_Pre(key_x) == 0) /* ������������� ����ȷ��������̬ */
							{		               			
									key_x->Status_Scan = enKEYx_Debounce;
								  key_x->Time_Press  = 0;
								  key_x->Flag_IfDataed = OFF;
								  key_x->Key_RetVal = enKey_No;
							}
							else
							{
								  key_x->Time_Press = 0;
							}
							break;
					case enKEYx_Debounce: /* ȷ��������̬ */
							if(Key_Pre(key_x) == 0)
							{
									key_x->Status_Scan = enKEYx_Confirm;
							}
							else
							{
									key_x->Status_Scan = enKEYx_Leisure;
								  KEY_RetValue = enKey_NO;
									key_x->Key_RetVal = enKey_No;
								  key_x->Time_Press = 0;
								  key_x->Flag_IfDataed = OFF;
								
							}
							break;
					case enKEYx_Confirm: /* ȷ��̬ */
							if(Key_Pre(key_x) == 1) /* �����ɿ� */
							{
								if(key_x->Time_Press < 50)
								{
										KEY_RetValue = key_x->key_name;
										key_x->Key_RetVal = enKey_Click;
										
								}
								else
								{
									  KEY_RetValue = enKey_NO;
									  key_x->Key_RetVal = enKey_No;
									  
								}
                if(key_x->Flag_AddDir == true) key_x->Flag_AddDir = false;
								else                           key_x->Flag_AddDir = true;												
                 key_x->Status_Scan = enKEYx_Leisure;
								 key_x->Time_Press=0;	
                 key_x->Flag_IfDataed = OFF;								
							}
							else
							{
								if(key_x->Time_Press > 50)
								{
									key_x->Key_RetVal = enKey_LongPress;    //����
								}
								if(key_x->Time_Press > 5000) key_x->Time_Press = 5000;   //�޷�
							}
							
							break;
					default:
							break;
			}

}

