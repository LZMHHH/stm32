/**
  ******************************************************************************
  * @file    usart3.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   这里使用接收中断.
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "usart1.h"

uint8_t SendBuff[DEBUG1_TX_BSIZE];
uint8_t ReadBuff[DEBUG1_RX_BSIZE];

//声明
void USART1_DMA_Config(void);

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(uint8_t priority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG1_UART_Tx_DMA_IRQ;   // 发送DMA通道的中断配置 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;      // 优先级设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG1_USART_IRQ;         //串口中断配置
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置   //DMA的
  * @param  无
  * @retval 无
  */
void USART1_Config(uint8_t priority)
{
	GPIO_InitTypeDef GPIO_InitStructurex;
	USART_InitTypeDef USART_InitStructurex;
	
	
	// 打开串口GPIO的时钟
	DEBUG1_USART_GPIO_APBxClkCmd(DEBUG1_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG1_USART_APBxClkCmd(DEBUG1_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructurex.GPIO_Pin = DEBUG1_USART_TX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructurex.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG1_USART_TX_GPIO_PORT, &GPIO_InitStructurex);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructurex.GPIO_Pin = DEBUG1_USART_RX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG1_USART_RX_GPIO_PORT, &GPIO_InitStructurex);
	
	//中断优先级配置
	NVIC_Configuration(priority);
	 // 串口 DMA 配置
	USART1_DMA_Config();  
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructurex.USART_BaudRate = DEBUG1_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructurex.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructurex.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructurex.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructurex.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructurex.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG1_USARTx, &USART_InitStructurex);
	
	
	
	// 使能串口接收中断（接收完产生的）
	//USART_ITConfig(DEBUG1_USARTx, USART_IT_RXNE, ENABLE);	
	// 使能串口空闲中断
	USART_ITConfig(DEBUG1_USARTx, USART_IT_IDLE, ENABLE);
	// 使能串口
	USART_Cmd(DEBUG1_USARTx, ENABLE);		
	// 开启DMA
	USART_DMACmd(DEBUG1_USARTx, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(DEBUG1_USARTx, USART_DMAReq_Rx, ENABLE);



  // 清除发送完成标志
	//USART_ClearFlag(USART3, USART_FLAG_TC);     
}

/**
  * @brief  USARTx TX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USART1_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		// 开启DMA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	  //////////////   TX    /////////////
	  // 关闭DMA
		DMA_Cmd (DEBUG1_UART_Tx_DMA_Channel,DISABLE);
	  // 恢复缺省值
	  DMA_DeInit(DEBUG1_UART_Tx_DMA_Channel);  
	  // 设置串口发送数据寄存器	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG1_USARTx->DR);
	  // 设置发送缓冲区首地址
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff; 
    // 设置外设位目标，内存缓冲区 ->外设寄存器  
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;      
    // 需要发送的字节数，这里其实可以设置为0，因为在实际要发送的时候，会重新设置次值	
    DMA_InitStructure.DMA_BufferSize = DEBUG1_TX_BSIZE;      
    // 外设地址不做增加调整，调整不调整是DMA自动实现的
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // 内存缓冲区地址增加调整
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // 外设数据宽度8位，1个字节	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// 内存数据宽度8位，1个字节
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// 单次传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // 优先级设置		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // 关闭内存到内存的DMA模式		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // 写入配置		
    DMA_Init(DEBUG1_UART_Tx_DMA_Channel, &DMA_InitStructure);
    // 清除DMA所有标志		
    DMA_ClearFlag(DEBUG1_UART_Tx_DMA_FLAG);       
    // 关闭DMA		
    DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, DISABLE); 
		// 开启发送DMA通道中断
    DMA_ITConfig(DEBUG1_UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);  


    /////////////////  RX   //////////////
    // 关闭DMA
		DMA_Cmd (DEBUG1_UART_Rx_DMA_Channel,DISABLE);
	  // 恢复缺省值
	  DMA_DeInit(DEBUG1_UART_Rx_DMA_Channel);  
	  // 设置串口发送数据寄存器	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG1_USARTx->DR);
	  // 设置发送缓冲区首地址
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ReadBuff; 
    // 设置外设位目标，外设寄存器->内存缓冲区   
	  DMA_InitStructure.DMA_DIR =  DMA_DIR_PeripheralSRC;      
    // 需要发送的字节数，这里其实可以设置为0，因为在实际要发送的时候，会重新设置次值	
    DMA_InitStructure.DMA_BufferSize = DEBUG1_RX_BSIZE;      
    // 外设地址不做增加调整，调整不调整是DMA自动实现的
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // 内存缓冲区地址增加调整
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // 外设数据宽度8位，1个字节	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// 内存数据宽度8位，1个字节
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// 单次传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // 优先级设置		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // 关闭内存到内存的DMA模式		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // 写入配置		
    DMA_Init(DEBUG1_UART_Rx_DMA_Channel, &DMA_InitStructure);
    // 清除DMA所有标志		
    DMA_ClearFlag(DEBUG1_UART_Rx_DMA_FLAG);    
		
    // 开启接收DMA通道，等待接收数据  		
    DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);                                 

	
}

//DMA----------
//开始发送
void Uart1_Start_DMA_Tx(uint16_t size)
{	
   	// 设置要发送的字节数目
    DEBUG1_UART_Tx_DMA_Channel->CNDTR = (uint16_t)size; 
	  //开始DMA发送
    DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, ENABLE);        
}
//发送完成中断
void DEBUG1_UART_Tx_DMA_IRQHandler(void)
{
    if(DMA_GetITStatus(DEBUG1_UART_Tx_DMA_FLAG))
    {
        DMA_ClearFlag(DEBUG1_UART_Tx_DMA_FLAG);         // 清除标志
			  DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, DISABLE);   // 关闭DMA通道   
        
    }
}
//接收  //中断   //可配合协议写
void DEBUG1_USART_IRQHandler(void)
{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	  static u8 num = 0;   //关系到多少个 20 字节  
	  static u8 index = 0;   //超字节时 前面的字节总和
	
    if(USART_GetITStatus(DEBUG1_USARTx, USART_IT_IDLE) != RESET)  // 空闲中断
    {
			  USART_ClearITPendingBit( DEBUG1_USARTx, USART_IT_IDLE );  //清除空闲中断
			  USART_ReceiveData(DEBUG1_USARTx); //读DR,只有读过一次，才能真正清除标志
			  USART_ClearFlag( DEBUG1_USARTx, USART_FLAG_IDLE );  //读SR其实就是清除标志
			
			  DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, DISABLE);       // 关闭DMA ，防止干扰
			  DMA_ClearFlag( DEBUG1_UART_Rx_DMA_FLAG );           // 清DMA标志位
			  num = DEBUG1_RX_BSIZE - DMA_GetCurrDataCounter(DEBUG1_UART_Rx_DMA_Channel); //获得接收到的字节数
			  DEBUG1_UART_Rx_DMA_Channel->CNDTR = DEBUG1_RX_BSIZE;    //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目
			  
			  

			  //Flage_StateRx = State_RTno;     //接收完成
			  //屏蔽这个的意思是处理处理完本次数据再开启接收
			  //DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);        //DMA 开启，等待数据。注意，如果中断发送数据帧的速率很快，MCU来不及处理此次接收到的数据，中断又发来数据的话，这里不能开启，否则数据会被覆盖。有2种方式解决。
			
#if DEBUG1_SAFETY
				xQueueSendFromISR(  xQueue_uart1Tx,               /* 消息队列的句柄 */
                    (void *)ReadBuff,                   /* 发送的消息内容 */
                            &xHigherPriorityTaskWoken); /* 高优先级任务是否被唤醒的状态保存 */

#else
				xQueueSendFromISR(  xQueue_uart1Tx,               /* 消息队列的句柄 */
				            (void *)&ReadBuff,                   /* 发送的消息内容 发送字符串的地址*/
                            &xHigherPriorityTaskWoken); /* 高优先级任务是否被唤醒的状态保存 */

#endif

				DEBUG1_UART_Rx_DMA_Channel->CMAR  = (uint32_t)ReadBuff; 					
				DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);

				
        USART_ReceiveData( DEBUG1_USARTx ); // Clear IDLE interrupt flag bit
    }
		
		//如果有高优先级任务要切换，就切换
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/* 发送数据，再次开发（待优化） */
void Uart1_DMA_SendString( char *SendString,short int size)
{
	if(size < 0)
	{
		size = strlen(SendString);
	}
	
	 *(SendBuff + size + 1) = '\0';
	 memcpy(SendBuff, SendString, size);
	 
 
	 Uart1_Start_DMA_Tx(size);
}





//普通
/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*****************  发送一个16位数 **********************/
void Usartx_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

//串口接收中断  函数  DEBUG1_USART_IRQHandler  写在外边了



