#ifndef usart_h
#define usart_h

#include "driverlib.h"

void send_data(unsigned char data);
void usart_init(void);
void sendSenser(int a_x,int a_y,int a_z,unsigned char _fu);



#endif
