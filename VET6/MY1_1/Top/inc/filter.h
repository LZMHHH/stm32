/**
  ******************************************************************************
  * @file    filter.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   卡尔曼滤波  及  一阶互补滤波
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */

#ifndef __FILTER_H
#define __FILTER_H
 
extern float angle_X,angle_Y,angle_Z, angle_dotX, angle_dotY, angle_dotZ; 

void Kalman_Filter(float Accel, float Gyro, int kind);		
void Yijielvbo(float angle_m, float gyro_m, int Kind);
#endif
