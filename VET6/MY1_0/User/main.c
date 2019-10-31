
/**
  ******************************************************************************
  * @file    main.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  * 实验平台:LZM
  * 
  * Wechat：qabc132321
  *
	* FreeRTOS  工程模板
  ******************************************************************************
  */

#include "includes.h"

//1 printf，  是把格式字符串输出到标准输出（一般是屏幕，可以重定向）。
//2 sprintf， 是把格式字符串输出到指定字符串中，所以参数比printf多一个char*。那就是目标字符串地址。
//3 fprintf， 是把格式字符串输出到指定文件设备中，所以参数笔printf多一个文件指针FILE*。


/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
void AppTaskCreate ( void );
void AppObjCreate  ( void );
//void vTaskLed      ( void * pvParameters );
//void vTaskKey      ( void * pvParameters );




/*
**********************************************************************************************************
											句柄变量声明
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskLed1  = NULL;  //LED任务
static TaskHandle_t xHandleTaskKey   = NULL;  //KEY任务
       TaskHandle_t xQueue_uart      = NULL;  //串口的消息队列




int main(void)
{
	/* 
	  在启动调度前，为了防止初始化STM32外设时有中断服务程序执行，这里禁止全局中断(除了NMI和HardFault)。
	  这样做的好处是：
	  1. 防止执行的中断服务程序中有FreeRTOS的API函数。
	  2. 保证系统正常启动，不受别的中断影响。
	  3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
	  在移植文件port.c中的函数prvStartFirstTask中会重新开启全局中断。通过指令cpsie i开启，__set_PRIMASK(1)
	  和cpsie i是等效的。
     */
	__set_PRIMASK(1);
	
	//bsp初始化
  bsp_Init();
	
	
	/* 创建任务 */
	AppTaskCreate();
	
	/* 创建消息 */
	AppObjCreate();
	
	/* 启动调度，开始执行任务 */
	vTaskStartScheduler();

	/* 
	  如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
	  heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
	

	  
	
}


/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
	
    xTaskCreate( vTaskLed,   	        /* 任务函数  */
                 "Task Led",     	    /* 任务名    */
                 512,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 16,                 	/* 任务优先级*/
                 &xHandleTaskLed1 );  /* 任务句柄  */
	
	  xTaskCreate( vTaskKey,   	        /* 任务函数  */
                 "Task Key",     	    /* 任务名    */
                 512,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 7,                 	/* 任务优先级*/
                 &xHandleTaskKey );   /* 任务句柄  */
	
	
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建任务通信机制
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
	char *SendString;
	 /* 创建Test_Queue */
  xQueue_uart = xQueueCreate((UBaseType_t ) 5,                 /* 消息队列的长度 */
                             (UBaseType_t ) DEBUG1_TX_BSIZE);   /* 消息的大小 */
	
	if(NULL != xQueue_uart)
	{
		SendString = "创建Test_Queue消息队列成功!\r\n";
		memcpy(SendBuff, SendString, 30);
    Uart1_Start_DMA_Tx(sizeof(SendBuff));
	}
}

