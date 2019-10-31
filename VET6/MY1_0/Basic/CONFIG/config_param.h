/*
*********************************************************************************************************
*
*	模块名称 : CONFIG_PARAM模块
*	文件名称 : config_param.h
*	说    明 : 这是底层驱动模块所有的h文件的汇总文件。 应用程序只需 #include config_param.h 即可，
*			  不需要#include 每个模块的 h 文件
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


/* 保存参数结构 */
typedef struct
{
	u8    version;     //版本号
	enum  language  language;
	

	
} ConfigParam_t;



#endif

/***************************** lss *********************************/
