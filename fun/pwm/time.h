#ifndef _time_h
#define _time_h

#include "driverlib.h"

extern int time,time1 ,time2,time3,time4;

void rtc_init(void);
void time_init(void);
#endif