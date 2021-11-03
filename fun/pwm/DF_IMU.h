#ifndef _imu_middle_H
#define _imu_middle_H

#include "icm.h"
#include "DF_Filter.h"


#define MIN(a, b) 	(((a) < (b)) ? (a) : (b))
#define MAX(a, b) 	(((a) > (b)) ? (a) : (b))
#define M_PIf       3.14159265358979323846f

void DF_IMUupdate(float gx, float gy, float gz, float ax, float ay, float az); 
void DF_Get_Eulerian_Angle(struct _out_angle *angle);   			//所得的只是 pitch roll
#endif

