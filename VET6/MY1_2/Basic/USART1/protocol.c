/**
  ******************************************************************************
  * @file    usart3.c
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
#include "protocol.h"



//����


/**   
  * @brief  
  * @param  
  * @retval 
  */



	/**   
  * @brief  ���ƴ�������  ���� 3
  * @param  
  * @retval 
  */
 void ProtocolCpyData3(void)
{

	memcpy(uart3.ReadProtocolString, uart3.ReadBuff,uart3.Read_Index + 1);  //���Բ� +1
	memset(uart3.ReadBuff, 0x00, sizeof(uart3.ReadBuff));
	//�������
	uart3.State_Rx = State_ReTno; 
	
  DEBUG3_UART_Rx_DMA_Channel->CMAR  = (u32)uart3.ReadBuff;	//�������ô洢����ַ
	DMA_Cmd(DEBUG3_UART_Rx_DMA_Channel, ENABLE);        //DMA �������ȴ����ݡ�ע�⣬����жϷ�������֡�����ʺܿ죬MCU����������˴ν��յ������ݣ��ж��ַ������ݵĻ������ﲻ�ܿ������������ݻᱻ���ǡ���2�ַ�ʽ�����
}

	/**   
  * @brief  ���ƴ�������  ���� 3
  * @param  
  * @retval 
  */
 void ProtocolCpyData3sem(void)
{

	memcpy(uart3.ReadProtocolString, uart3.ReadBuff,uart3.Read_Index + 1);  //���Բ� +1
	memset(uart3.ReadBuff, 0x00, sizeof(uart3.ReadBuff));
	//�������
	//uart3.State_Rx = State_ReTno; 
	
//  DEBUG3_UART_Rx_DMA_Channel->CMAR  = (u32)uart3.ReadBuff;	//�������ô洢����ַ
//	DMA_Cmd(DEBUG3_UART_Rx_DMA_Channel, ENABLE);        //DMA �������ȴ����ݡ�ע�⣬����жϷ�������֡�����ʺܿ죬MCU����������˴ν��յ������ݣ��ж��ַ������ݵĻ������ﲻ�ܿ������������ݻᱻ���ǡ���2�ַ�ʽ�����
}
	
	/**   
  * @brief  ����
  * @param  
  * @retval ������ͬ�ĵ�һλλ��
  */
int StringFind(const char *pSrc, const char *pDst)  
{  
    int i, j;  
    for (i=0; pSrc[i]!='\0'; i++)  
    {  
        if(pSrc[i]!=pDst[0])  
            continue;         
        j = 0;  
        while(pDst[j]!='\0' && pSrc[i+j]!='\0')  
        {  
            j++;  
            if(pDst[j]!=pSrc[i+j])  
            break;  
        }  
        if(pDst[j]=='\0')  
            return i;  
    }  
    return -1;  
} 

/**   
  * @brief    ֡����
* @param      pDst:ֻ�������ַ�
  * @retval 
  * @explain  $U,AP+12345#  ��  5λ����
  */	
long int Protocol_DecodeInt(const char *pSrc, const char *pDst)
{
	int      site;
	
	long int pI = 0;
	
	char     pStr[10] = {0};
		
	site = StringFind((const char *)pSrc, (const char *)pDst);

	memcpy(pStr,pSrc + site + 3,5);     //ע����ֵ��λ��
	 if(*(pSrc + site + 2) == '+')
		 pI = atof(pStr);
	 else
		 pI = -atof(pStr);
	 
	 return pI;
}

/**   
  * @brief    ֡����  ���� 3 
* @param      pSrc:  ����ַ��ı�ͷ��  pnum: ���֡�  pSite: pSrc�ַ��ĸ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  $A,R,AP+12345#  ��  5λ����
  */	
char Protocol3_EncodeInt(const char *pSrc,long int pnum, u8 pSite)
{
   
   static char ProtocolStringT[DEBUG_TX_BSIZE] = {0};		 
	 static char numS[10];   //pnum���ַ���
	 
	 char Flage_Reend = 0;   //������ɷ��صı�־λ
	 
	 if(uart3.State_Report == State_ReTno)
	 {
			memset(numS, 0x00, sizeof(numS));  
			memset(ProtocolStringT, 0x00, sizeof(ProtocolStringT));  
		
			if(pnum>0)
			{
				memcpy(ProtocolStringT,pSrc,pSite);
				memcpy(ProtocolStringT+pSite,"+",1);
			}
			else
			{
				memcpy(ProtocolStringT,pSrc,pSite);
				memcpy(ProtocolStringT+pSite,"-",1);
				pnum = -pnum;
			}
			sprintf(numS,"%ld",pnum);
			if(pnum < 100000 && pnum >9999)
			{
				memcpy(ProtocolStringT+pSite+1,numS,5);
				
			}
			if(pnum < 10000 && pnum >999)
			{
				memcpy(ProtocolStringT+pSite+1,"0",1);
				memcpy(ProtocolStringT+pSite+2,numS,4);
			}
			if(pnum < 1000 && pnum >99)
			{
				memcpy(ProtocolStringT+pSite+1,"00",2);
				memcpy(ProtocolStringT+pSite+3,numS,3);
			}
			if(pnum < 100 && pnum >9)
			{
				memcpy(ProtocolStringT+pSite+1,"000",3);
				memcpy(ProtocolStringT+pSite+4,numS,2);
			}
			if(pnum < 10)
			{
				memcpy(ProtocolStringT+pSite+1,"0000",4);
				memcpy(ProtocolStringT+pSite+5,numS,1);
			}
			*(ProtocolStringT+pSite+6)= '#';
			
			uart3.State_Report = State_ReTing;					
		}
		if(uart3.State_Report == State_ReTing && uart3.State_Tx == State_RTno)  //���з���
		{
			Usart3_DMA_SendString(ProtocolStringT,pSite+7);
			uart3.State_Report = State_ReTed;
		}
		if(uart3.State_Report == State_ReTed && uart3.State_Tx == state_RTed) //��ɷ���
		{
			uart3.State_Tx = State_RTno;   //���ڱ�־����
			uart3.State_Report = State_ReTno;      //״̬��λ		
      Flage_Reend	= 1;		
		}	
    
    return Flage_Reend;		
}
/**   
  * @brief    ����ʽ�������ݻ��崦��  ���� 3 
  * @param      pSrc:  Դ���ݡ�  pnum: ���֡�  pSite: Դ���ݳ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  
  */	
char Free3_SendString(const char *pSrc, u8 pSite)
{
	if(uart3.State_Free == State_ReTno)  //���ɿ���ʱ
	{
		uart3.SendProtocolString[0] = pSite;
		memcpy(uart3.SendProtocolString+1,pSrc,pSite);
		uart3.State_Free = State_ReTing;    //���뷢��״̬		
		return 1;
	}
	return 0;
}
/**   
  * @brief    ����ʽ�������ݻ��崦��  ���� 3 
  * @param      pSrc:  Դ���ݡ�  pnum: ���֡�  pSite: Դ���ݳ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  
  */	
char Free3_SendNum(const char *pSrc,long int pnum, u8 pSite)
{
	static char numS[10];   //pnum���ַ���
	
	if(uart3.State_Free == State_ReTno)  //���ɿ���ʱ
	{
		uart3.SendProtocolString[0] = pSite + 7;  //���� = �ַ��� +12345#
		if(pnum>0)
			{
				memcpy(uart3.SendProtocolString+1,pSrc,pSite);
				memcpy(uart3.SendProtocolString+1+pSite,"+",1);
			}
			else
			{
				memcpy(uart3.SendProtocolString+1,pSrc,pSite);
				memcpy(uart3.SendProtocolString+1+pSite,"-",1);
				pnum = -pnum;
			}
			sprintf(numS,"%ld",pnum);
			if(pnum < 100000 && pnum >9999)
			{
				memcpy(uart3.SendProtocolString+pSite+2,numS,5);
				
			}
			if(pnum < 10000 && pnum >999)
			{
				memcpy(uart3.SendProtocolString+pSite+2,"0",1);
				memcpy(uart3.SendProtocolString+pSite+3,numS,4);
			}
			if(pnum < 1000 && pnum >99)
			{
				memcpy(uart3.SendProtocolString+pSite+2,"00",2);
				memcpy(uart3.SendProtocolString+pSite+4,numS,3);
			}
			if(pnum < 100 && pnum >9)
			{
				memcpy(uart3.SendProtocolString+pSite+2,"000",3);
				memcpy(uart3.SendProtocolString+pSite+5,numS,2);
			}
			if(pnum < 10)
			{
				memcpy(uart3.SendProtocolString+pSite+2,"0000",4);
				memcpy(uart3.SendProtocolString+pSite+6,numS,1);
			}
			*(uart3.SendProtocolString+pSite+7)= '#';
		uart3.State_Free = State_ReTing;    //���뷢��״̬		
		return 1;
	}
	return 0;
}
/**   
  * @brief    ִ�� ����ʽ�������� ���� 3 
  * @param      pSrc:  Դ���ݡ�  pnum: ���֡�  pSite: Դ���ݳ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  
  */	
void Free3_Send_Con(void)
{
	if(uart3.State_Free == State_ReTing && uart3.State_Tx == State_RTno)  //���з���
		{
			Usart3_DMA_SendString(uart3.SendProtocolString+1,uart3.SendProtocolString[0]);
			uart3.State_Free = State_ReTed;
		}
		if((uart3.State_Free == State_ReTed && uart3.State_Tx == state_RTed)) //��ɷ���
		{
			uart3.State_Tx   = State_RTno;   //���ڱ�־����
			uart3.State_Free = State_ReTno;      //״̬��λ	
      memset(uart3.SendProtocolString, 0x00, sizeof(uart3.SendProtocolString));  		//���帴λ	
		}
}

///////  ����   //////////////////////////////////////////////////////////////////


// /////// ����  3  //////////////////////////////////////////////////////////////
	/**   
  * @brief  Э�����   ����  ���� 3
  * @param  
  * @retval �Լ�����Э�飺ͷ+��������1����������2������Ϊ1������Ϊ2������Ϊ3������Ϊ4#
  */
void Protocol3(void)
{
	long int Hh;
	
	//������
	if(uart3.ReadProtocolString[1] == 'K')
	{	
		switch(uart3.ReadProtocolString[3])
		{
			case '1':  Key_PU.Key_RetVal = enKey_Click;
			  break;
			case '2':  Key_PD.Key_RetVal = enKey_Click;
			  break;
			case '3':  Key_PL.Key_RetVal = enKey_Click;
			  break;
			case '4':  Key_PR.Key_RetVal = enKey_Click;
			  break;
			case '5':  Key_PM.Key_RetVal = enKey_Click;
			  break;	
			case '6':  save_FlashData(1);
								 Num_SaveFlashCountA++;
			  break;	
			case '7':  save_FlashData(2);
								 Num_SaveFlashCountB++;
			  break;	
			
			case 'A':  if(Flag_Led_Switch == ON) 	  Flag_Led_Switch = OFF;
						     else 		                    Flag_Led_Switch = ON;
			  break;
      case 'B':  switch(Flag_LedMode)
								 {
									 case enLEDM_R:
																Flag_LedMode = enLEDM_Z1;
																break;
									 case enLEDM_G:
																Flag_LedMode = enLEDM_R;
																break; 
									 case enLEDM_B:
																Flag_LedMode = enLEDM_G;
																break;
									 case enLEDM_T1:
																Flag_LedMode = enLEDM_B;
																break;
									 case enLEDM_Z1:
																Flag_LedMode = enLEDM_T1;
																break;
									 default :
										            Flag_LedMode = enLEDM_Z1;
																break;
								 }
								 break;
			  break;	
      case 'C':  if(LedA.flag_kg == ON) 	    
			           {
									 LedA.flag_kg = OFF;
									 Free3_SendString("$K,C0#",6);
								 }
						     else 
                 {
									 LedA.flag_kg = ON;
									 Free3_SendString("$K,C1#",6);
								 }
			  break;	
      case 'D':  if(LedB.flag_kg == ON) 	    
			           {
									 LedB.flag_kg = OFF;
									 Free3_SendString("$K,D0#",6);
								 }
						     else 
                 {
									 LedB.flag_kg = ON;
									 Free3_SendString("$K,D1#",6);
								 }
			  break;
      case 'E':  if(LedC.flag_kg == ON) 	    
			           {
									 LedC.flag_kg = OFF;
									 Free3_SendString("$K,E0#",6);
								 }
						     else 
                 {
									 LedC.flag_kg = ON;
									 Free3_SendString("$K,E1#",6);
								 }
			  break;
      case 'F':  if(LedD.flag_kg == ON) 	    
			           {
									 LedD.flag_kg = OFF;
									 Free3_SendString("$K,F0#",6);
								 }
						     else 
                 {
									 LedD.flag_kg = ON;
									 Free3_SendString("$K,F1#",6);
								 }
			  break;
      case 'G':  if(Fmq.flag_kg == ON) 	    
			           {
									 Fmq.flag_kg = OFF;
									 Free3_SendString("$K,G0#",6);
								 }
						     else 
                 {
									 Fmq.flag_kg = ON;
									 Free3_SendString("$K,G1#",6);
								 }
			  break;
			case 'H':  if(pb.flag_kg == ON) 	    
			           {
									 pb.flag_kg = OFF;
									 Free3_SendString("$K,H0#",6);
								 }
						     else 
                 {
									 pb.flag_kg = ON;
									 Free3_SendString("$K,H1#",6);
								 }
			  break;
			case 'I':  if(motor1.flag_kg == ON) 	    
			           {
									 motor1.flag_kg = OFF;
									 Free3_SendString("$K,I0#",6);
								 }
						     else 
                 {
									 motor1.flag_kg = ON;
									 Free3_SendString("$K,I1#",6);
								 }
			  break;
			case 'J':  if(ClockNo1.Clock_Switch == ON) 	    
			           {
									 ClockNo1.Clock_Switch = OFF;
									 Free3_SendString("$K,J0#",6);
								 }
						     else 
                 {
									 ClockNo1.Clock_Switch = ON;
									 Free3_SendString("$K,J1#",6);
								 }
			  break;
			case 'K':  if(ClockNo2.Clock_Switch == ON) 	    
			           {
									 ClockNo2.Clock_Switch = OFF;
									 Free3_SendString("$K,K0#",6);
								 }
						     else 
                 {
									 ClockNo2.Clock_Switch = ON;
									 Free3_SendString("$K,K1#",6);
								 }
			  break;
								 
      
		}	
	}
	
	//������
	if(uart3.ReadProtocolString[1] == 'D')
	{	
		//rgb ����
		if(uart3.ReadProtocolString[3] == 'R')
		{
			//rgb ����
			if(uart3.ReadProtocolString[4] == 'l')
			{
				  // $D,Rl+12345# 
				  Num_LedLight = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rl")/1000.0;
			}
			//rgb ��ɫ
			if(uart3.ReadProtocolString[4] == 'r')
			{
				  // $D,Rr+12345# 
				  Num_LedRatio_R = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rr");
			}
			//rgb ��ɫ
			if(uart3.ReadProtocolString[4] == 'g')
			{
				  // $D,Rg+12345# 
				  Num_LedRatio_G = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rg");
			}
			//rgb ��ɫ
			if(uart3.ReadProtocolString[4] == 'b')
			{
				  // $D,Rb+12345# 
				  Num_LedRatio_B = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rb");
			}
		}
			   
	}
	
	//������
	if(uart3.ReadProtocolString[1] == 'U')
	{
		
		//����ʱ��  1
		if(uart3.ReadProtocolString[3] == 'C')
		{
			if(uart3.ReadProtocolString[4] == 'h')
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Ch");
			  ClockNo1.Clock_Hour = Hh;
			  Free3_SendString("$P,Cm#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 'm')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Cm");
			  ClockNo1.Clock_Minute = Hh;
			  Free3_SendString("$P,ok#",6);   //�������
			}
		}
		//����ʱ��  2
		if(uart3.ReadProtocolString[3] == 'H')
		{
			if(uart3.ReadProtocolString[4] == 'h')
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Hh");
			  ClockNo2.Clock_Hour = Hh;
			  Free3_SendString("$P,Hm#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 'm')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Hm");
			  ClockNo2.Clock_Minute = Hh;
			  Free3_SendString("$P,ok#",6);   //�������
			}
		}
		
	  //ʱ����
		if(uart3.ReadProtocolString[3] == 'T')
		{
						
			if(uart3.ReadProtocolString[4] == 'Y')   //��
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TY");
			  Set_TimeX.SetN_Year = Hh-2000;
			  Free3_SendString("$P,TM#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 'M')   //��
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TM");
			  Set_TimeX.SetN_Month = Hh;
			  Free3_SendString("$P,TD#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 'D')   //��
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TD");
			  Set_TimeX.SetN_Day = Hh;
			  Free3_SendString("$P,Th#",6);    //�ƻ�����  ���� ʱ
			}
			if(uart3.ReadProtocolString[4] == 'h')   //ʱ
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Th");
			  Set_TimeX.SetN_Hour = Hh;
			  Free3_SendString("$P,Tm#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 'm')   //��
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Tm");
			  Set_TimeX.SetN_Minute = Hh;
			  Free3_SendString("$P,Ts#",6);    //�ƻ�����  ���� ��
			}
			if(uart3.ReadProtocolString[4] == 's')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Ts");
				Set_TimeX.SetN_Second = Hh;
			  DSSet_TimeAll(&Set_TimeX);   //�趨ʱ��
			  Free3_SendString("$P,Tok#",7);   //�������
			}
		}
	}
	
	
	
	//�������  ��λ�ַ���
	//Flage_StateRx = State_ReTno;  
	memset(uart3.ReadProtocolString, 0x00, sizeof(uart3.ReadProtocolString));  
}
// ����+�ۺϴ��� ����
// ����  3 ����֡�ϱ���
u8 Reported_EnvironmentData3(void)
{
	u8 Flag_ReportedEnd = 0;   //���һ֡��־λ
	
	
		
	return 0;
}


// ����  3 �ϱ�����
u8 Reported_Data3(void)
{
	u8 Flag_ReportedEnd = 0;   //���һ֡��־λ
	
//	// �豸 A
//	//�� 1 ֡
//	if(Plan_ReportedTiming3 == 1)   //  �¶�     $R,AE,ET+12345#
//	{
//		Flag_ReportedEnd = 0;
//	  Flag_ReportedEnd = Protocol3_EncodeInt("$R,AE,ET",DHT11_Data.Temp*10,8);       //  
//		if(Flag_ReportedEnd) {Static_ReAppFrame = State_ReTed;return 1;}            //  ��֡��ɣ��ȴ���һ֡
//	}
//	
//	
//	
//	//��λ
//	if(Plan_ReportedTiming3 > 14)  Plan_ReportedTiming3 = 0;
		
	return 0;
}























