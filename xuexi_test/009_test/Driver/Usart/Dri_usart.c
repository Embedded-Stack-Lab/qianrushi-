#include "Dri_usart.h"

void   Dri_USART_Init(void)
{

    // GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO结构体变量，用于配置GPIO引脚
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//使能GPIOA和USART1时钟
    // GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//设置GPIO引脚为USART1的TX引脚
    // GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;//设置GPIO引脚为复用推挽输出模式
    // GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;//设置GPIO引脚速度为50MHz
    // GPIO_Init(GPIOA,&GPIO_InitStructure);

    // GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//设置GPIO引脚为USART1的RX引脚
    // GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//设置GPIO引脚为输入浮空模式
    // GPIO_Init(GPIOA,&GPIO_InitStructure);

    // USART_InitTypeDef USART_InitStructure;//定义USART结构体变量，用于配置USART
    // USART_InitStructure.USART_BaudRate = 115200;//设置USART波特率为115200
    // USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//设置USART硬件流控制为无
    // USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//设置USART模式为发送和接收
    // USART_InitStructure.USART_Parity = USART_Parity_No;//设置USART校验位为无
    // USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置USART停止位为1位
    // USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置USART字长为8位
    // USART_Init(USART1,&USART_InitStructure);//初始化USART1
    // USART_Cmd(USART1,ENABLE);//使能USART1


    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // GPIO_InitStructure.GPIO_Speed=
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStruture;
    USART_InitStruture.USART_BaudRate            = 115200;
    USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruture.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruture.USART_Parity              = USART_Parity_No;
    USART_InitStruture.USART_StopBits            = USART_StopBits_1;
    USART_InitStruture.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruture);
    USART_Cmd(USART1, ENABLE); //


}


void Dri_USART_SendByte(uint8_t byte){

    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待发送完成

    USART_SendData(USART1,byte);//发送字节

    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//等待发送完成
}
uint8_t Dri_USART_ReceiveByte(void){

    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);//等待接收完成

    return USART_ReceiveData(USART1);//返回接收字节

}


