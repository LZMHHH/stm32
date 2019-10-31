#include "show.h"


//更改数据后才用   内部
void Para_Update(void)
{
  if(Page_Index_Last != Page_Index)
  {
    Page_Index_Last = Page_Index;
    OLED_Clear();
  }
  
  if(Page_Index==1)
  {

  }
	
	if(Page_Index==2)
  {
      
		  Speed_YKBasic    = Para_Control1[1];
			Speed_YKMaxBasic = Para_Control1[2];
			Speed_BZBasic    = Para_Control1[3];
			Num_BZTime       = Para_Control1[4];
			Flage_BZVal      = Para_Control1[5];
			Speed_XJBasic    = Para_Control1[6];
			Speed_Add        = Para_Control1[7];
			
  }

}

//预备参数,防止无线控制更新参数   内部
void Para_Prepare(void)
{
  if(Page_Index_Last != Page_Index)
  {
    Page_Index_Last = Page_Index;
    OLED_Clear();
  }
  
	
	if(Page_Index==1)
  {

  }
	if(Page_Index==2)
  {
      Para_Control1[1]=Speed_YKBasic;
			Para_Control1[2]=Speed_YKMaxBasic;
			Para_Control1[3]=Speed_BZBasic;
			Para_Control1[4]=Num_BZTime;
			Para_Control1[5]=Flage_BZVal;
			Para_Control1[6]=Speed_XJBasic;
			Para_Control1[7]=Speed_Add;
  }

}



/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void Show_ZUI(void)
{

	
	OLED_ShowChar(115,0,'P',1);
  OLED_ShowNum(121,0,Page_Index,1,0,1);
  
	if(Page_Index == 0)
  {
	  OLED_ShowString(0,0,"BAT",1);                          //显示电池电压
    OLED_ShowNum(27, 0,BAT_Voltage/1000.0,2,1,1);  
    OLED_ShowString(55,0,"V",1);                          //显示电池电压单位
    //OLED_ShowNum(78, 0,Step_Size[Step_Index],4,1,1);            //显示调节步进值
		
		//1
    OLED_ShowString(0,1,"Mode:",1);
		switch(State_CarMode)
		{
			case Mode_YK:
				   OLED_ShowString(80,1,"   YK",1);
			     break;
			case Mode_BZ:
				   OLED_ShowString(80,1,"   BZ",1);
			     break;
			case Mode_XJ:
				   OLED_ShowString(80,1,"   XJ",1);
			     break;
			case Mode_GS:
				   OLED_ShowString(80,1,"   GS",1);
			     break;
			default :
				   OLED_ShowString(80,1,"error",1);
			     break;
		}
    		
		//2
    OLED_ShowString(0,2,"Stat:",1);
		switch(State_CarAction)
		{
			case enSTOP:
				   OLED_ShowString(80,2," stop",1);
			     break;
			case enSTATIC:
				   OLED_ShowString(80,2,"static",1);
			     break;
			case enRUN:
				   OLED_ShowString(80,2,"  run",1);
			     break;
			default :
				   OLED_ShowString(80,2,"other",1);
			     break;
		}
    		
		//3
    OLED_ShowString(0,3,"BZ  :",1);
		if(Flag_BZControl == OFF) OLED_ShowString(80,3,"  OFF",1);
		else                      OLED_ShowString(80,3,"   ON",1);
		
		//4
		OLED_ShowString(0,4,"XJ  :",1);
		if(Flag_XJControl == OFF) OLED_ShowString(80,4,"  OFF",1);
		else                      OLED_ShowString(80,4,"   ON",1);
		
		//5
		OLED_ShowString(0,5,"LC  :",1);
		OLED_ShowNum(42,5,DistanceM,3,2,1);  
		OLED_ShowString(104,5,"M",1);
		
		//6
		OLED_ShowString(0,6,"CSB:",1);
	  OLED_ShowNum(48,6,Distance,4,0,1);
	  OLED_ShowString(80,6,"   mm",1);
						
		
	}
	

if(Page_Index == 1)
  {
		
		OLED_ShowString(0,0,"BAT",1);                         //显示电池电压
    OLED_ShowNum(27, 0,BAT_Voltage/1000.0,2,1,1);  
    OLED_ShowString(55,0,"V",1);                          //显示电池电压单位
    OLED_ShowNum(70, 0,Step_Size[Step_Index],4,1,1);      //显示调节步进值
		
		//1行
		if(Para_Index == 1 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,1,"Mode:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,1,"Mode:",1);
		if(Para_Index == 1 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				switch(State_CarMode)
				{
					case Mode_YK:
							 OLED_ShowString(80,1,"   YK",1);
							 break;
					case Mode_BZ:
							 OLED_ShowString(80,1,"   BZ",1);
							 break;
					case Mode_XJ:
							 OLED_ShowString(80,1,"   XJ",1);
							 break;
					default :
							 OLED_ShowString(80,1,"error",1);
							 break;
				}
			  Oled_Colour = 0;
		}
		else 
		{
			switch(State_CarMode)
			{
				case Mode_YK:
						 OLED_ShowString(80,1,"   YK",1);
						 break;
				case Mode_BZ:
						 OLED_ShowString(80,1,"   BZ",1);
						 break;
				case Mode_XJ:
						 OLED_ShowString(80,1,"   XJ",1);
						 break;
				default :
						 OLED_ShowString(80,1,"error",1);
						 break;
			}
		}
		//2
		if(Para_Index == 2 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,2,"BZ  :",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,2,"BZ  :",1);
		if(Para_Index == 2 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				if(Flag_BZControl == OFF) OLED_ShowString(80,2,"  OFF",1);
		    else                      OLED_ShowString(80,2,"   ON",1);
			  Oled_Colour = 0;
		}
		else 
		{
			if(Flag_BZControl == OFF) OLED_ShowString(80,2,"  OFF",1);
		  else                      OLED_ShowString(80,2,"   ON",1);
		}
		//3
		if(Para_Index == 3 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,3,"XJ  :",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,3,"XJ  :",1);
		if(Para_Index == 3 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				if(Flag_XJControl == OFF) OLED_ShowString(80,3,"  OFF",1);
		    else                      OLED_ShowString(80,3,"   ON",1);
			  Oled_Colour = 0;
		}
		else 
		{
			if(Flag_XJControl == OFF) OLED_ShowString(80,3,"  OFF",1);
		  else                      OLED_ShowString(80,3,"   ON",1);
		}
		//4
		if(Para_Index == 4 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,4,"Sp_T:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,4,"Sp_T:",1);
		if(Para_Index == 4 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,4,Speed_Turn,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,4,Speed_Turn,4,0,1);
		//5
		if(Para_Index == 5 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,5,"Sp_G:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,5,"Sp_G:",1);
		if(Para_Index == 5 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,5,Speed_GS,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,5,Speed_GS,4,0,1);
		//6
		if(Para_Index == 6 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,6,"Turn_D:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,6,"Turn_D:",1);
		if(Para_Index == 6 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(70,6,Turn_Kd,3,1,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(70,6,Turn_Kd,3,1,1);
		//7
		if(Para_Index == 7 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,7,"Fla_DC:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,7,"Fla_DC:",1);
		if(Para_Index == 7 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(70,7,Flag_Voltage_Val,3,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(70,7,Flag_Voltage_Val,3,0,1);
		OLED_ShowChar(121,7,'V',1);		
		}

	if(Page_Index == 2)
  {
		
		OLED_ShowString(0,0,"BAT",1);                          //显示电池电压
    OLED_ShowNum(27, 0,BAT_Voltage/1000.0,2,1,1);  
    OLED_ShowString(55,0,"V",1);                          //显示电池电压单位
    OLED_ShowNum(70, 0,Step_Size[Step_Index],4,1,1);            //显示调节步进值
		
		//1行
		if(Para_Index == 1 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,1,"Sp_YKb:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,1,"Sp_YKb:",1);
		if(Para_Index == 1 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,1,Speed_YKBasic,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,1,Speed_YKBasic,4,0,1);
		//2
		if(Para_Index == 2 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,2,"Sp_YKm:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,2,"Sp_YKm:",1);
		if(Para_Index == 2 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,2,Speed_YKMaxBasic,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,2,Speed_YKMaxBasic,4,0,1);
		//3
		if(Para_Index == 3 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,3,"Sp_BZb:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,3,"Sp_BZb:",1);
		if(Para_Index == 3 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,3,Speed_BZBasic,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,3,Speed_BZBasic,4,0,1);
		//4
		if(Para_Index == 4 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,4,"Nu_BZt:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,4,"Nu_BZt:",1);
		if(Para_Index == 4 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(90,4,Num_BZTime,3,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(90,4,Num_BZTime,3,0,1);
		//5
		if(Para_Index == 5 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,5,"Fl_BZv:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,5,"Fl_BZv:",1);
		if(Para_Index == 5 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,5,Flage_BZVal,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,5,Flage_BZVal,4,0,1);
		//6
		if(Para_Index == 6 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,6,"Sp_XJb:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,6,"Sp_XJb:",1);
		if(Para_Index == 6 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,6,Speed_XJBasic,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,6,Speed_XJBasic,4,0,1);
		//7
		if(Para_Index == 7 && Para_IfControl == false)
    {
        Oled_Colour = 1;     //fanzhuan
			  OLED_ShowString(0,7,"Sp_Add:",1);
			  Oled_Colour = 0;
		}
		else OLED_ShowString(0,7,"Sp_Add:",1);
		if(Para_Index == 7 && Para_IfControl == true)
    {
        Oled_Colour = 1;     //fanzhuan
				OLED_ShowNum(84,7,Speed_Add,4,0,1);
			  Oled_Colour = 0;
		}
		else OLED_ShowNum(84,7,Speed_Add,4,0,1);
		}
    
	
	
	if(Page_Index == 3)
  {
		
		OLED_ShowString(0,0,"BAT",1);                         //显示电池电压
    OLED_ShowNum(27, 0,BAT_Voltage/1000.0,2,1,1);  
    OLED_ShowString(55,0,"V",1);                          //显示电池电压单位
    OLED_ShowNum(70, 0,Step_Size[Step_Index],4,1,1);      //显示调节步进值
		
		//1
	  OLED_ShowString(0,1,"XJ  :",1);
		OLED_ShowNum(70, 1,BZL,1,0,1);  
		OLED_ShowNum(80, 1,XJ1,1,0,1);  
		OLED_ShowNum(90, 1,XJ2,1,0,1);  
		OLED_ShowNum(100, 1,XJ3,1,0,1);  
		OLED_ShowNum(110, 1,XJ4,1,0,1);  
		OLED_ShowNum(120, 1,BZR,1,0,1);  
		
		//2
		OLED_ShowString(0,2,"XJs :",1);
		switch(XJ_RetValue)
		 {
			 case 0x00: 
								 OLED_ShowString(80,2,"    M",1);
								 break;
			 case 0x08: 
								 OLED_ShowString(84,2,"   L1",1);
								 break;
			 case 0x04: 
								 OLED_ShowString(84,2,"   L2",1);
								 break;
			 case 0x02: 
								 OLED_ShowString(84,2,"   R1",1);
								 break;
			 case 0x01: 
								 OLED_ShowString(84,2,"   R2",1);
								 break;
			 case 0x0C: 
								 OLED_ShowString(84,2,"   LA",1);
								 break;
			 case 0x03: 
								 OLED_ShowString(84,2,"   RA",1);
								 break;
			 default:  OLED_ShowString(84,2,"    M",1);
								 break;
		 }
		 
	  	//3
		  OLED_ShowString(0,3,"AnY :",1);
      OLED_ShowNum(78,3,Angle_BalanceY,3,2,1);
		 
		 //6
		  OLED_ShowString(0,6,"En  :",1);
			OLED_ShowNum(42,6,Encoder_Left,4,0,1);
			OLED_ShowNum(90,6,Encoder_Right,4,0,1);		 

			//7
	    OLED_ShowString(0,7,"Mot :",1);                       
			OLED_ShowNum(36,7,OUTL_Val,5,0,1);                       
			OLED_ShowNum(84,7,OUTR_Val,5,0,1);

	 
	}
}


