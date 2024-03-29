#include "usart.h"

void usart_init(void)
{
   GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN4 + GPIO_PIN5
        );
    
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 104;
    param.firstModReg = 0;
    param.secondModReg = 1;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if(STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param))
    {
        return;
    }
    
    USCI_A_UART_enable(USCI_A1_BASE);
    
    USCI_A_UART_clearInterrupt(USCI_A1_BASE,
                               USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(USCI_A1_BASE,
                                USCI_A_UART_RECEIVE_INTERRUPT);

    __enable_interrupt();
}

void send_data(unsigned char data)
{
  USCI_A_UART_transmitData(USCI_A1_BASE, data);
}

#define  BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	)  )
#define  BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define  BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define  BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


unsigned char DataTOSend[40];
void sendSenser(int a_x,int a_y,int a_z,unsigned char _fu)
{
	unsigned char _cnt=0;

	DataTOSend[_cnt++]=0xAA;
	DataTOSend[_cnt++]=0xFF;
	DataTOSend[_cnt++]=0x03;
	DataTOSend[_cnt++]=7;
	
	DataTOSend[_cnt++]=BYTE0(a_x);
	DataTOSend[_cnt++]=BYTE1(a_x);
	
	DataTOSend[_cnt++]=BYTE0(a_y);
	DataTOSend[_cnt++]=BYTE1(a_y);
	
	DataTOSend[_cnt++]=BYTE0(a_z);
	DataTOSend[_cnt++]=BYTE1(a_z);
	
	DataTOSend[_cnt++]=_fu;
	unsigned char sc=0;
	unsigned char ac=0;

	for(unsigned char i=0; i < (DataTOSend[3]+4); i++)
	{
	 sc += DataTOSend[i]; 
	 ac += sc; 
	}
	DataTOSend[_cnt++]=sc;
	DataTOSend[_cnt++]=ac;
	
	for(unsigned char temp=0;temp<_cnt;temp++)
		{
			send_data(DataTOSend[temp]);
		}
}



char receivedData;

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
 switch(__even_in_range(UCA1IV,4))
 {
 case 2:
           receivedData = USCI_A_UART_receiveData(USCI_A1_BASE);
           send_data(receivedData);
           break;
 default: break;          
 }
}




