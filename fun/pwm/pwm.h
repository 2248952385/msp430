#ifndef pwm_h
#define pwm_h

#include "driverlib.h"

void pwm_init(int DUTY_CYCLE1,int DUTY_CYCLE2,int TIMER_PERIOD);
void set_pwm1(int duty);
void set_pwm2(int duty);
void set_pwm3(int duty);
void set_pwm4(int duty);

#endif

