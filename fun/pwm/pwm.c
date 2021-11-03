#include "pwm.h"


void pwm_init(int DUTY_CYCLE1,int DUTY_CYCLE2,int TIMER_PERIOD)
{

  P2DIR |= BIT0+BIT1+BIT3+BIT4;                       // P2.0 and P2.1 output
  P2SEL |= BIT0+BIT1+BIT3+BIT4;                       // P2.0 and P2.1 options select
  TA1CCR0 = TIMER_PERIOD-1;                          // PWM Period
  TA2CCR0 = TIMER_PERIOD-1;                          // PWM Period
  TA1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA1CCR1 = DUTY_CYCLE1;                            // CCR1 PWM duty cycle
  TA2CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA2CCR1 = DUTY_CYCLE1;                            // CCR1 PWM duty cycle
  TA1CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA1CCR2 = DUTY_CYCLE2;                            // CCR2 PWM duty cycle
  TA2CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA2CCR2 = DUTY_CYCLE2;                            // CCR2 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_1 + TACLR;         // ACLK, up mode, clear TAR
  TA2CTL = TASSEL_2 + MC_1 + TACLR;
}

void set_pwm1(int duty)
{
  TA1CCR1 = duty;
}
void set_pwm2(int duty)
{
  TA2CCR1 = duty;
}
void set_pwm3(int duty)
{
  TA1CCR2 = duty;
}
void set_pwm4(int duty)
{
  TA2CCR2 = duty;
}