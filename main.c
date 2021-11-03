#include "driverlib.h"
#include "pwm.h"
#include "usart.h"
#include "time.h"
#include "adc.h"
#include "icm.h"
#include "DF_IMU.h"
#include "DF_Filter.h"
void main(void)
{
   WDT_A_hold(WDT_A_BASE);                   //Stop WDT    
   usart_init();
   OLED_Init();
   rtc_init();
   //adc_init();
   //ADC12CTL0 |= ADC12SC; 
   time_init();
   ICM20602_Init();
   Create_Butter_Filter(&Butter1);
   Bilinear(&Butter1);
   while(1)
   {
    if(time >=2)
     {   
       time =0 ;
       ICM20602_Updata_get();
       ACC_IIR_Filter(&acc, &filter_acc, &Butter1);		  
       GYRO_IIR_Filter(&gyro, &filter_gyro, &Butter1);			  
       Get_Radian(&filter_gyro, &SI_gyro);
       DF_IMUupdate(SI_gyro.x, SI_gyro.y, SI_gyro.z, filter_acc.x, filter_acc.y, filter_acc.z);
       //sendSenser(acc.x,acc.y,acc.z,1);
     }
    if(time1>10)
    {
      time1 = 0;
      DF_Get_Eulerian_Angle(&out_angle);
      sendSenser(out_angle.pitch*100,out_angle.roll*100,out_angle.yaw*100,1);
    }
   }
    
 }
