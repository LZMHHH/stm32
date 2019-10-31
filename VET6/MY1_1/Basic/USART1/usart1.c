/**
  ******************************************************************************
  * @file    usart3.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   ����ʹ�ý����ж�.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "usart1.h"

uint8_t SendBuff[DEBUG1_TX_BSIZE];
uint8_t ReadBuff[DEBUG1_RX_BSIZE];

//����
void USART1_DMA_Config(void);

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(uint8_t priority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG1_UART_Tx_DMA_IRQ;   // ����DMAͨ�����ж����� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;      // ���ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG1_USART_IRQ;         //�����ж�����
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������   //DMA��
  * @param  ��
  * @retval ��
  */
void USART1_Config(uint8_t priority)
{
	GPIO_InitTypeDef GPIO_InitStructurex;
	USART_InitTypeDef USART_InitStructurex;
	
	
	// �򿪴���GPIO��ʱ��
	DEBUG1_USART_GPIO_APBxClkCmd(DEBUG1_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG1_USART_APBxClkCmd(DEBUG1_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructurex.GPIO_Pin = DEBUG1_USART_TX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructurex.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG1_USART_TX_GPIO_PORT, &GPIO_InitStructurex);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructurex.GPIO_Pin = DEBUG1_USART_RX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG1_USART_RX_GPIO_PORT, &GPIO_InitStructurex);
	
	//�ж����ȼ�����
	NVIC_Configuration(priority);
	 // ���� DMA ����
	USART1_DMA_Config();  
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructurex.USART_BaudRate = DEBUG1_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructurex.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructurex.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructurex.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructurex.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructurex.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG1_USARTx, &USART_InitStructurex);
	
	
	
	// ʹ�ܴ��ڽ����жϣ�����������ģ�
	//USART_ITConfig(DEBUG1_USARTx, USART_IT_RXNE, ENABLE);	
	// ʹ�ܴ��ڿ����ж�
	USART_ITConfig(DEBUG1_USARTx, USART_IT_IDLE, ENABLE);
	// ʹ�ܴ���
	USART_Cmd(DEBUG1_USARTx, ENABLE);		
	// ����DMA
	USART_DMACmd(DEBUG1_USARTx, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(DEBUG1_USARTx, USART_DMAReq_Rx, ENABLE);



  // ���������ɱ�־
	//USART_ClearFlag(USART3, USART_FLAG_TC);     
}

/**
  * @brief  USARTx TX DMA ���ã��ڴ浽����(USART1->DR)
  * @param  ��
  * @retval ��
  */
void USART1_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	  //////////////   TX    /////////////
	  // �ر�DMA
		DMA_Cmd (DEBUG1_UART_Tx_DMA_Channel,DISABLE);
	  // �ָ�ȱʡֵ
	  DMA_DeInit(DEBUG1_UART_Tx_DMA_Channel);  
	  // ���ô��ڷ������ݼĴ���	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG1_USARTx->DR);
	  // ���÷��ͻ������׵�ַ
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff; 
    // ��������λĿ�꣬�ڴ滺���� ->����Ĵ���  
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;      
    // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ	
    DMA_InitStructure.DMA_BufferSize = DEBUG1_TX_BSIZE;      
    // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // �ڴ滺������ַ���ӵ���
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // �������ݿ��8λ��1���ֽ�	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// �ڴ����ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// ���δ���ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // ���ȼ�����		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // �ر��ڴ浽�ڴ��DMAģʽ		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // д������		
    DMA_Init(DEBUG1_UART_Tx_DMA_Channel, &DMA_InitStructure);
    // ���DMA���б�־		
    DMA_ClearFlag(DEBUG1_UART_Tx_DMA_FLAG);       
    // �ر�DMA		
    DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, DISABLE); 
		// ��������DMAͨ���ж�
    DMA_ITConfig(DEBUG1_UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);  


    /////////////////  RX   //////////////
    // �ر�DMA
		DMA_Cmd (DEBUG1_UART_Rx_DMA_Channel,DISABLE);
	  // �ָ�ȱʡֵ
	  DMA_DeInit(DEBUG1_UART_Rx_DMA_Channel);  
	  // ���ô��ڷ������ݼĴ���	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG1_USARTx->DR);
	  // ���÷��ͻ������׵�ַ
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ReadBuff; 
    // ��������λĿ�꣬����Ĵ���->�ڴ滺����   
	  DMA_InitStructure.DMA_DIR =  DMA_DIR_PeripheralSRC;      
    // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ	
    DMA_InitStructure.DMA_BufferSize = DEBUG1_RX_BSIZE;      
    // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // �ڴ滺������ַ���ӵ���
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // �������ݿ��8λ��1���ֽ�	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// �ڴ����ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// ���δ���ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // ���ȼ�����		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // �ر��ڴ浽�ڴ��DMAģʽ		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // д������		
    DMA_Init(DEBUG1_UART_Rx_DMA_Channel, &DMA_InitStructure);
    // ���DMA���б�־		
    DMA_ClearFlag(DEBUG1_UART_Rx_DMA_FLAG);    
		
    // ��������DMAͨ�����ȴ���������  		
    DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);                                 

	
}

//DMA----------
//��ʼ����
void Uart1_Start_DMA_Tx(uint16_t size)
{	
   	// ����Ҫ���͵��ֽ���Ŀ
    DEBUG1_UART_Tx_DMA_Channel->CNDTR = (uint16_t)size; 
	  //��ʼDMA����
    DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, ENABLE);        
}
//��������ж�
void DEBUG1_UART_Tx_DMA_IRQHandler(void)
{
    if(DMA_GetITStatus(DEBUG1_UART_Tx_DMA_FLAG))
    {
        DMA_ClearFlag(DEBUG1_UART_Tx_DMA_FLAG);         // �����־
			  DMA_Cmd(DEBUG1_UART_Tx_DMA_Channel, DISABLE);   // �ر�DMAͨ��   
        
    }
}
//����  //�ж�   //�����Э��д
void DEBUG1_USART_IRQHandler(void)
{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	  static u8 num = 0;   //��ϵ�����ٸ� 20 �ֽ�  
	  static u8 index = 0;   //���ֽ�ʱ ǰ����ֽ��ܺ�
	
    if(USART_GetITStatus(DEBUG1_USARTx, USART_IT_IDLE) != RESET)  // �����ж�
    {
			  USART_ClearITPendingBit( DEBUG1_USARTx, USART_IT_IDLE );  //��������ж�
			  USART_ReceiveData(DEBUG1_USARTx); //��DR,ֻ�ж���һ�Σ��������������־
			  USART_ClearFlag( DEBUG1_USARTx, USART_FLAG_IDLE );  //��SR��ʵ���������־
			
			  DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, DISABLE);       // �ر�DMA ����ֹ����
			  DMA_ClearFlag( DEBUG1_UART_Rx_DMA_FLAG );           // ��DMA��־λ
			  num = DEBUG1_RX_BSIZE - DMA_GetCurrDataCounter(DEBUG1_UART_Rx_DMA_Channel); //��ý��յ����ֽ���
			  DEBUG1_UART_Rx_DMA_Channel->CNDTR = DEBUG1_RX_BSIZE;    //  ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
			  
			  

			  //Flage_StateRx = State_RTno;     //�������
			  //�����������˼�Ǵ������걾�������ٿ�������
			  //DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);        //DMA �������ȴ����ݡ�ע�⣬����жϷ�������֡�����ʺܿ죬MCU����������˴ν��յ������ݣ��ж��ַ������ݵĻ������ﲻ�ܿ������������ݻᱻ���ǡ���2�ַ�ʽ�����
			
#if DEBUG1_SAFETY
				xQueueSendFromISR(  xQueue_uart1Tx,               /* ��Ϣ���еľ�� */
                    (void *)ReadBuff,                   /* ���͵���Ϣ���� */
                            &xHigherPriorityTaskWoken); /* �����ȼ������Ƿ񱻻��ѵ�״̬���� */

#else
				xQueueSendFromISR(  xQueue_uart1Tx,               /* ��Ϣ���еľ�� */
				            (void *)&ReadBuff,                   /* ���͵���Ϣ���� �����ַ����ĵ�ַ*/
                            &xHigherPriorityTaskWoken); /* �����ȼ������Ƿ񱻻��ѵ�״̬���� */

#endif

				DEBUG1_UART_Rx_DMA_Channel->CMAR  = (uint32_t)ReadBuff; 					
				DMA_Cmd(DEBUG1_UART_Rx_DMA_Channel, ENABLE);

				
        USART_ReceiveData( DEBUG1_USARTx ); // Clear IDLE interrupt flag bit
    }
		
		//����и����ȼ�����Ҫ�л������л�
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/* �������ݣ��ٴο��������Ż��� */
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





//��ͨ
/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*****************  ����һ��16λ�� **********************/
void Usartx_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

//���ڽ����ж�  ����  DEBUG1_USART_IRQHandler  д�������



