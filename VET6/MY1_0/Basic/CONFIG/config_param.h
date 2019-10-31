/*
*********************************************************************************************************
*
*	ģ������ : CONFIG_PARAMģ��
*	�ļ����� : config_param.h
*	˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include config_param.h ���ɣ�
*			  ����Ҫ#include ÿ��ģ��� h �ļ�
*
*	
*
*********************************************************************************************************
*/

#ifndef _CONFIG_PARAM_H
#define _CONFIG_PARAM_H

#include "includes.h"

enum language
{
	SIMPLE_CHINESE,
	ENGLISH,
};


/* ��������ṹ */
typedef struct
{
	u8    version;     //�汾��
	enum  language  language;
	

	
} ConfigParam_t;



#endif

/***************************** lss *********************************/
