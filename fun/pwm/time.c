#include "time.h"

void rtc_init(void)
{
  /*P5SEL |= BIT2+BIT3;                       

  UCSCTL6 &= ~XT2OFF;                       //xt2  4mhz
  UCSCTL3 |= SELREF_2;                      

  UCSCTL4 |= SELA_2;                       // ACLK=REFO  32.768khz ,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);                                      
    SFRIFG1 &= ~OFIFG;                      
  }while (SFRIFG1&OFIFG);                 

  UCSCTL6 &= ~XT2DRIVE0;                        
  UCSCTL4 |= SELS_5 + SELM_5;   */
  
  UCSCTL3 |= SELREF_2;                     
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                 
  UCSCTL0 = 0x0000;                         
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 24MHz operation
  UCSCTL2 = FLLD_1 + 374;                   // Set DCO Multiplier for 12MHz
                                            // (N + 1) * FLLRef = Fdco
                                            // (374 + 1) * 32768 = 12MHz
                                            // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0);                  // Enable the FLL control loop

  __delay_cycles(375000);
	
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG); 
  
}


void time_init(void)
{
    TA0R = 0; 
    TA0CCTL0 = CCIE; 
    TA0CCR0 = 11999; 
    TA0CTL = TASSEL_2 + MC_1 + TACLR;       //smclk 
    __enable_interrupt();
}
 
int time=0,time1 = 0 ,time2=0,time3=0,time4=0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timea(void)
 {
    time++;
    time1++;
    time2++;
    time3++;
    time4++;
 }


