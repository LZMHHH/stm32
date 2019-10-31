/**
  ******************************************************************************
  * @file    usart3.c
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
#include "protocol.h"



//声明


/**   
  * @brief  
  * @param  
  * @retval 
  */



	/**   
  * @brief  复制串口数据  串口 3
  * @param  
  * @retval 
  */
 void ProtocolCpyData3(void)
{

	memcpy(uart3.ReadProtocolString, uart3.ReadBuff,uart3.Read_Index + 1);  //可以不 +1
	memset(uart3.ReadBuff, 0x00, sizeof(uart3.ReadBuff));
	//调用完毕
	uart3.State_Rx = State_ReTno; 
	
  DEBUG3_UART_Rx_DMA_Channel->CMAR  = (u32)uart3.ReadBuff;	//重新设置存储器地址
	DMA_Cmd(DEBUG3_UART_Rx_DMA_Channel, ENABLE);        //DMA 开启，等待数据。注意，如果中断发送数据帧的速率很快，MCU来不及处理此次接收到的数据，中断又发来数据的话，这里不能开启，否则数据会被覆盖。有2种方式解决。
}

	/**   
  * @brief  复制串口数据  串口 3
  * @param  
  * @retval 
  */
 void ProtocolCpyData3sem(void)
{

	memcpy(uart3.ReadProtocolString, uart3.ReadBuff,uart3.Read_Index + 1);  //可以不 +1
	memset(uart3.ReadBuff, 0x00, sizeof(uart3.ReadBuff));
	//调用完毕
	//uart3.State_Rx = State_ReTno; 
	
//  DEBUG3_UART_Rx_DMA_Channel->CMAR  = (u32)uart3.ReadBuff;	//重新设置存储器地址
//	DMA_Cmd(DEBUG3_UART_Rx_DMA_Channel, ENABLE);        //DMA 开启，等待数据。注意，如果中断发送数据帧的速率很快，MCU来不及处理此次接收到的数据，中断又发来数据的话，这里不能开启，否则数据会被覆盖。有2种方式解决。
}
	
	/**   
  * @brief  搜索
  * @param  
  * @retval 返回相同的第一位位置
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
  * @brief    帧解码
* @param      pDst:只能两个字符
  * @retval 
  * @explain  $U,AP+12345#  。  5位整数
  */	
long int Protocol_DecodeInt(const char *pSrc, const char *pDst)
{
	int      site;
	
	long int pI = 0;
	
	char     pStr[10] = {0};
		
	site = StringFind((const char *)pSrc, (const char *)pDst);

	memcpy(pStr,pSrc + site + 3,5);     //注意数值的位数
	 if(*(pSrc + site + 2) == '+')
		 pI = atof(pStr);
	 else
		 pI = -atof(pStr);
	 
	 return pI;
}

/**   
  * @brief    帧编码  串口 3 
* @param      pSrc:  五个字符的标头。  pnum: 数字。  pSite: pSrc字符的个数
  * @retval   返回 1 证明数据已经发出。
  * @explain  $A,R,AP+12345#  。  5位整数
  */	
char Protocol3_EncodeInt(const char *pSrc,long int pnum, u8 pSite)
{
   
   static char ProtocolStringT[DEBUG_TX_BSIZE] = {0};		 
	 static char numS[10];   //pnum的字符串
	 
	 char Flage_Reend = 0;   //发送完成返回的标志位
	 
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
		if(uart3.State_Report == State_ReTing && uart3.State_Tx == State_RTno)  //空闲发送
		{
			Usart3_DMA_SendString(ProtocolStringT,pSite+7);
			uart3.State_Report = State_ReTed;
		}
		if(uart3.State_Report == State_ReTed && uart3.State_Tx == state_RTed) //完成发送
		{
			uart3.State_Tx = State_RTno;   //串口标志空闲
			uart3.State_Report = State_ReTno;      //状态复位		
      Flage_Reend	= 1;		
		}	
    
    return Flage_Reend;		
}
/**   
  * @brief    自由式发送数据缓冲处理  串口 3 
  * @param      pSrc:  源数据。  pnum: 数字。  pSite: 源数据长度
  * @retval   返回 1 证明数据已经发出。
  * @explain  
  */	
char Free3_SendString(const char *pSrc, u8 pSite)
{
	if(uart3.State_Free == State_ReTno)  //自由空闲时
	{
		uart3.SendProtocolString[0] = pSite;
		memcpy(uart3.SendProtocolString+1,pSrc,pSite);
		uart3.State_Free = State_ReTing;    //进入发送状态		
		return 1;
	}
	return 0;
}
/**   
  * @brief    自由式发送数据缓冲处理  串口 3 
  * @param      pSrc:  源数据。  pnum: 数字。  pSite: 源数据长度
  * @retval   返回 1 证明数据已经发出。
  * @explain  
  */	
char Free3_SendNum(const char *pSrc,long int pnum, u8 pSite)
{
	static char numS[10];   //pnum的字符串
	
	if(uart3.State_Free == State_ReTno)  //自由空闲时
	{
		uart3.SendProtocolString[0] = pSite + 7;  //长度 = 字符串 +12345#
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
		uart3.State_Free = State_ReTing;    //进入发送状态		
		return 1;
	}
	return 0;
}
/**   
  * @brief    执行 自由式发送数据 串口 3 
  * @param      pSrc:  源数据。  pnum: 数字。  pSite: 源数据长度
  * @retval   返回 1 证明数据已经发出。
  * @explain  
  */	
void Free3_Send_Con(void)
{
	if(uart3.State_Free == State_ReTing && uart3.State_Tx == State_RTno)  //空闲发送
		{
			Usart3_DMA_SendString(uart3.SendProtocolString+1,uart3.SendProtocolString[0]);
			uart3.State_Free = State_ReTed;
		}
		if((uart3.State_Free == State_ReTed && uart3.State_Tx == state_RTed)) //完成发送
		{
			uart3.State_Tx   = State_RTno;   //串口标志空闲
			uart3.State_Free = State_ReTno;      //状态复位	
      memset(uart3.SendProtocolString, 0x00, sizeof(uart3.SendProtocolString));  		//缓冲复位	
		}
}

///////  开发   //////////////////////////////////////////////////////////////////


// /////// 串口  3  //////////////////////////////////////////////////////////////
	/**   
  * @brief  协议解码   蓝牙  串口 3
  * @param  
  * @retval 自己定义协议：头+控制命令1，控制命令2，数据为1，数据为2，数据为3，数据为4#
  */
void Protocol3(void)
{
	long int Hh;
	
	//按键类
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
	
	//数据类
	if(uart3.ReadProtocolString[1] == 'D')
	{	
		//rgb 亮度
		if(uart3.ReadProtocolString[3] == 'R')
		{
			//rgb 亮度
			if(uart3.ReadProtocolString[4] == 'l')
			{
				  // $D,Rl+12345# 
				  Num_LedLight = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rl")/1000.0;
			}
			//rgb 红色
			if(uart3.ReadProtocolString[4] == 'r')
			{
				  // $D,Rr+12345# 
				  Num_LedRatio_R = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rr");
			}
			//rgb 绿色
			if(uart3.ReadProtocolString[4] == 'g')
			{
				  // $D,Rg+12345# 
				  Num_LedRatio_G = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rg");
			}
			//rgb 蓝色
			if(uart3.ReadProtocolString[4] == 'b')
			{
				  // $D,Rb+12345# 
				  Num_LedRatio_B = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Rb");
			}
		}
			   
	}
	
	//更新类
	if(uart3.ReadProtocolString[1] == 'U')
	{
		
		//闹钟时间  1
		if(uart3.ReadProtocolString[3] == 'C')
		{
			if(uart3.ReadProtocolString[4] == 'h')
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Ch");
			  ClockNo1.Clock_Hour = Hh;
			  Free3_SendString("$P,Cm#",6);    //计划进度  请求 分
			}
			if(uart3.ReadProtocolString[4] == 'm')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Cm");
			  ClockNo1.Clock_Minute = Hh;
			  Free3_SendString("$P,ok#",6);   //进度完成
			}
		}
		//闹钟时间  2
		if(uart3.ReadProtocolString[3] == 'H')
		{
			if(uart3.ReadProtocolString[4] == 'h')
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Hh");
			  ClockNo2.Clock_Hour = Hh;
			  Free3_SendString("$P,Hm#",6);    //计划进度  请求 分
			}
			if(uart3.ReadProtocolString[4] == 'm')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Hm");
			  ClockNo2.Clock_Minute = Hh;
			  Free3_SendString("$P,ok#",6);   //进度完成
			}
		}
		
	  //时间类
		if(uart3.ReadProtocolString[3] == 'T')
		{
						
			if(uart3.ReadProtocolString[4] == 'Y')   //年
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TY");
			  Set_TimeX.SetN_Year = Hh-2000;
			  Free3_SendString("$P,TM#",6);    //计划进度  请求 月
			}
			if(uart3.ReadProtocolString[4] == 'M')   //月
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TM");
			  Set_TimeX.SetN_Month = Hh;
			  Free3_SendString("$P,TD#",6);    //计划进度  请求 日
			}
			if(uart3.ReadProtocolString[4] == 'D')   //日
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"TD");
			  Set_TimeX.SetN_Day = Hh;
			  Free3_SendString("$P,Th#",6);    //计划进度  请求 时
			}
			if(uart3.ReadProtocolString[4] == 'h')   //时
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Th");
			  Set_TimeX.SetN_Hour = Hh;
			  Free3_SendString("$P,Tm#",6);    //计划进度  请求 分
			}
			if(uart3.ReadProtocolString[4] == 'm')   //分
			{
				Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Tm");
			  Set_TimeX.SetN_Minute = Hh;
			  Free3_SendString("$P,Ts#",6);    //计划进度  请求 秒
			}
			if(uart3.ReadProtocolString[4] == 's')
			{
			  Hh = Protocol_DecodeInt((const char *)uart3.ReadProtocolString,"Ts");
				Set_TimeX.SetN_Second = Hh;
			  DSSet_TimeAll(&Set_TimeX);   //设定时间
			  Free3_SendString("$P,Tok#",7);   //进度完成
			}
		}
	}
	
	
	
	//处理完毕  复位字符串
	//Flage_StateRx = State_ReTno;  
	memset(uart3.ReadProtocolString, 0x00, sizeof(uart3.ReadProtocolString));  
}
// 发送+综合处理 数据
// 串口  3 （按帧上报）
u8 Reported_EnvironmentData3(void)
{
	u8 Flag_ReportedEnd = 0;   //完成一帧标志位
	
	
		
	return 0;
}


// 串口  3 上报数据
u8 Reported_Data3(void)
{
	u8 Flag_ReportedEnd = 0;   //完成一帧标志位
	
//	// 设备 A
//	//第 1 帧
//	if(Plan_ReportedTiming3 == 1)   //  温度     $R,AE,ET+12345#
//	{
//		Flag_ReportedEnd = 0;
//	  Flag_ReportedEnd = Protocol3_EncodeInt("$R,AE,ET",DHT11_Data.Temp*10,8);       //  
//		if(Flag_ReportedEnd) {Static_ReAppFrame = State_ReTed;return 1;}            //  本帧完成，等待下一帧
//	}
//	
//	
//	
//	//复位
//	if(Plan_ReportedTiming3 > 14)  Plan_ReportedTiming3 = 0;
		
	return 0;
}























