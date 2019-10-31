/**
  ******************************************************************************
  * @file    usart1.h
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
#ifndef __USART1_H
#define	__USART1_H


#include "includes.h" 

#define  DEBUG1_USARTx                   USART1
#define  DEBUG1_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG1_USART_APBxClkCmd          RCC_APB2PeriphClockCmd
#define  DEBUG1_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG1_USART_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  DEBUG1_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG1_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG1_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG1_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG1_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG1_USART_IRQ                USART1_IRQn
#define  DEBUG1_USART_IRQHandler         USART1_IRQHandler

//DMA配置
// 一次发送的数据量
#define  DEBUG1_TX_BSIZE                   80
#define  DEBUG1_RX_BSIZE                   80
#define  DEBUG1_UART_Tx_DMA_Channel        DMA1_Channel4   // 串口对应的DMA请求通道
#define  DEBUG1_UART_Tx_DMA_FLAG           DMA1_FLAG_GL4//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 
#define  DEBUG1_UART_Tx_DMA_IRQ            DMA1_Channel4_IRQn
#define  DEBUG1_UART_Tx_DMA_IRQHandler     DMA1_Channel4_IRQHandler
#define  DEBUG1_UART_Rx_DMA_Channel        DMA1_Channel5   // 串口对应的DMA请求通道
#define  DEBUG1_UART_Rx_DMA_FLAG           DMA1_FLAG_GL5//DMA1_FLAG_TC3 | DMA1_FLAG_TE3 
#define  DEBUG1_UART_Rx_DMA_IRQ            DMA1_Channel5_IRQn
#define  DEBUG1_UART_Rx_DMA_IRQHandler     DMA1_Channel5_IRQHandler

extern  uint8_t SendBuff[DEBUG1_TX_BSIZE];
extern  uint8_t ReadBuff[DEBUG1_RX_BSIZE];



void USART1_Config(uint8_t priority);
void Usar1_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usar1_SendString( USART_TypeDef * pUSARTx, char *str);
void Usar1_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

//DMA
void Uart1_Start_DMA_Tx(uint16_t size);
void Usart1_DMA_SendString( char *SendString,u8 size);


#endif /* __USART_H */
