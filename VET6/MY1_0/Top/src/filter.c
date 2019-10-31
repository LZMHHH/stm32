/**
  ******************************************************************************
  * @file    filter.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "filter.h"
 
float K1 =0.02; 
float angle_X,angle_Y,angle_Z, angle_dotX, angle_dotY, angle_dotZ; 	
float Q_angle=0.001;// 过程噪声的协方差
float Q_gyro=0.003;//0.003 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
float R_angle=0.5;// 测量噪声的协方差 既测量偏差
float dt=0.005;//                 
char  C_0 = 1;
// X
float Q_bias_X, Angle_err_X;
float PCt_0_X, PCt_1_X, E_X;
float K_0_X, K_1_X, t_0_X, t_1_X;
float Pdot_X[4] ={0,0,0,0};
float PP_X[2][2] = { { 1, 0 },{ 0, 1 } };

// Y
float Q_bias_Y, Angle_err_Y;
float PCt_0_Y, PCt_1_Y, E_Y;
float K_0_Y, K_1_Y, t_0_Y, t_1_Y;
float Pdot_Y[4] ={0,0,0,0};
float PP_Y[2][2] = { { 1, 0 },{ 0, 1 } };

// Z
float Q_bias_Z, Angle_err_Z;
float PCt_0_Z, PCt_1_Z, E_Z;
float K_0_Z, K_1_Z, t_0_Z, t_1_Z;
float Pdot_Z[4] ={0,0,0,0};
float PP_Z[2][2] = { { 1, 0 },{ 0, 1 } };

/**************************************************************************
函数功能：简易卡尔曼滤波
入口参数：加速度、角速度
返回  值：无
**************************************************************************/
void Kalman_Filter(float Accel,float Gyro,int Kind)		
{
	if( Kind == 1)
	{
			angle_X+=(Gyro - Q_bias_X) * dt; //先验估计
			Pdot_X[0]=Q_angle - PP_X[0][1] - PP_X[1][0]; // Pk-先验估计误差协方差的微分

			Pdot_X[1]=-PP_X[1][1];
			Pdot_X[2]=-PP_X[1][1];
			Pdot_X[3]=Q_gyro;
			PP_X[0][0] += Pdot_X[0] * dt;     // Pk-先验估计误差协方差微分的积分
			PP_X[0][1] += Pdot_X[1] * dt;     // =先验估计误差协方差
			PP_X[1][0] += Pdot_X[2] * dt;
			PP_X[1][1] += Pdot_X[3] * dt;
				
			Angle_err_X = Accel - angle_X;	  //zk-先验估计
			
			PCt_0_X = C_0 * PP_X[0][0];
			PCt_1_X = C_0 * PP_X[1][0];
			
			E_X = R_angle + C_0 * PCt_0_X;
			
			K_0_X = PCt_0_X / E_X;
			K_1_X = PCt_1_X / E_X;
			
			t_0_X = PCt_0_X;
			t_1_X = C_0 * PP_X[0][1];

			PP_X[0][0] -= K_0_X * t_0_X;		     //后验估计误差协方差
			PP_X[0][1] -= K_0_X * t_1_X;
			PP_X[1][0] -= K_1_X * t_0_X;
			PP_X[1][1] -= K_1_X * t_1_X;
				
			angle_X	+= K_0_X * Angle_err_X;	     //后验估计
			Q_bias_X	+= K_1_X * Angle_err_X;	   //后验估计
			angle_dotX   = Gyro - Q_bias_X;	 //输出值(后验估计)的微分=角速度			
  }
	if( Kind == 2)
	{
			angle_Y+=(Gyro - Q_bias_Y) * dt; //先验估计
			Pdot_Y[0]=Q_angle - PP_Y[0][1] - PP_Y[1][0]; // Pk-先验估计误差协方差的微分

			Pdot_Y[1]=-PP_Y[1][1];
			Pdot_Y[2]=-PP_Y[1][1];
			Pdot_Y[3]=Q_gyro;
			PP_Y[0][0] += Pdot_Y[0] * dt;     // Pk-先验估计误差协方差微分的积分
			PP_Y[0][1] += Pdot_Y[1] * dt;     // =先验估计误差协方差
			PP_Y[1][0] += Pdot_Y[2] * dt;
			PP_Y[1][1] += Pdot_Y[3] * dt;
				
			Angle_err_Y = Accel - angle_Y;	  //zk-先验估计
			
			PCt_0_Y = C_0 * PP_Y[0][0];
			PCt_1_Y = C_0 * PP_Y[1][0];
			
			E_Y = R_angle + C_0 * PCt_0_Y;
			
			K_0_Y = PCt_0_Y / E_Y;
			K_1_Y = PCt_1_Y / E_Y;
			
			t_0_Y = PCt_0_Y;
			t_1_Y = C_0 * PP_Y[0][1];

			PP_Y[0][0] -= K_0_Y * t_0_Y;		     //后验估计误差协方差
			PP_Y[0][1] -= K_0_Y * t_1_Y;
			PP_Y[1][0] -= K_1_Y * t_0_Y;
			PP_Y[1][1] -= K_1_Y * t_1_Y;
				
			angle_Y	+= K_0_Y * Angle_err_Y;	     //后验估计
			Q_bias_Y	+= K_1_Y * Angle_err_Y;	   //后验估计
			angle_dotY   = Gyro - Q_bias_Y;	 //输出值(后验估计)的微分=角速度	
  }
	if( Kind == 3)
	{
			angle_Z+=(Gyro - Q_bias_Z) * dt; //先验估计
			Pdot_Z[0]=Q_angle - PP_Z[0][1] - PP_Z[1][0]; // Pk-先验估计误差协方差的微分

			Pdot_Z[1]=-PP_Z[1][1];
			Pdot_Z[2]=-PP_Z[1][1];
			Pdot_Z[3]=Q_gyro;
			PP_Z[0][0] += Pdot_Z[0] * dt;     // Pk-先验估计误差协方差微分的积分
			PP_Z[0][1] += Pdot_Z[1] * dt;     // =先验估计误差协方差
			PP_Z[1][0] += Pdot_Z[2] * dt;
			PP_Z[1][1] += Pdot_Z[3] * dt;
				
			Angle_err_Z = Accel - angle_Z;	  //zk-先验估计
			
			PCt_0_Z = C_0 * PP_Z[0][0];
			PCt_1_Z = C_0 * PP_Z[1][0];
			
			E_Z = R_angle + C_0 * PCt_0_Z;
			
			K_0_Z = PCt_0_Z / E_Z;
			K_1_Z = PCt_1_Z / E_Z;
			
			t_0_Z = PCt_0_Z;
			t_1_Z = C_0 * PP_Z[0][1];

			PP_Z[0][0] -= K_0_Z * t_0_Z;		     //后验估计误差协方差
			PP_Z[0][1] -= K_0_Z * t_1_Z;
			PP_Z[1][0] -= K_1_Z * t_0_Z;
			PP_Z[1][1] -= K_1_Z * t_1_Z;
				
			angle_Z	+= K_0_Z * Angle_err_Z;	     //后验估计
			Q_bias_Z	+= K_1_Z * Angle_err_Z;	   //后验估计
			angle_dotZ   = Gyro - Q_bias_Z;	 //输出值(后验估计)的微分=角速度
  }
}

/**************************************************************************
函数功能：一阶互补滤波
入口参数：加速度、角速度
返回  值：无
**************************************************************************/
void Yijielvbo(float angle_m, float gyro_m,int Kind)
{
	if( Kind == 1)
	{
   angle_X = K1 * angle_m+ (1-K1) * (angle_X + gyro_m * 0.005);
	}
	
	if( Kind == 2)
	{
   angle_Y = K1 * angle_m+ (1-K1) * (angle_Y + gyro_m * 0.005);
	}
	
	if( Kind == 3)
	{
   angle_Z = K1 * angle_m+ (1-K1) * (angle_Z + gyro_m * 0.005);
	}
}

