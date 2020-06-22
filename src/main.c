
#include "stm32f4xx.h"

char str[100]="Vien_Handsome\n";

void delay()
{
	for (uint32_t i=0;i<0xffffff;i++);
}

uint16_t USART_GetChar()
{
    // Doi nhan duoc du lieu
	while (!USART_GetFlagStatus(USART2, USART_FLAG_RXNE));
    // Doc du lieu nhan duoc
	return USART_ReceiveData(USART2);
}


void USART_PutChar(char c)
{
    // Cho cho den khi san sang nhan du lieu
	while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
    // Gui du lieu
  USART_SendData(USART2, c);
}

void USART_PutString(char *s)
{
    // 
	while (*s)
  {
		USART_PutChar(*s++);
  }
}



int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


  GPIO_InitTypeDef GPIO_InitDef;
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitDef.GPIO_Speed = GPIO_High_Speed;
  GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
  GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitDef);


  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);//PA2->Tx
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);//PA3->Rx

    //GPIOA
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

    // USART2
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART_InitStruct);
  USART_Cmd(USART2, ENABLE);

	GPIO_SetBits(GPIOE, GPIO_Pin_8);
	while (1)
	{
		USART_PutString(str);
		delay();
	}
}
