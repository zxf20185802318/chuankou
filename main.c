#include "stm32f10x.h"

void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //串口时钟使能，GPIO 时钟使能
	
	USART_DeInit(USART1);                                 //复位串口 1 
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);                     //GPIO 端口模式设置
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //串口参数初始化
	
	USART_Init(USART1,&USART_InitStrue);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //开启中断
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;           //初始化 NVIC
	NVIC_Init(&NVIC_InitStrue);
	
	USART_Cmd(USART1,ENABLE);                              //使能串口1
	
}

void USART1_IRQHandler(void)
{
	u8 a;
	 if(USART_GetITStatus(USART1,USART_IT_RXNE))
 {
    a= USART_ReceiveData(USART1); 
     USART_SendData(USART1,a);   
  }
}
 
 int main(void)
 {	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init();
	 while(1);
	 
 }
