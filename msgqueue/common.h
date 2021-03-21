/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : common.h
* Author      :
* Version     : V1.0
* Description :
* Journal     : 2021-03-19 init v1.0
* Brief       : Blog address: https://blog.csdn.net/qq_38750572?spm=1001.2014.3001.5343
* Others      :
********************************************************************************
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#define DEBUG_LOG_SUPPORT

#ifdef PRINT_ERR
#undef PRINT_ERR
#endif
#define PRINT_ERR(format,x...)    \
do{ printf( "ERROR: func: %s line: %04d info: " format,          \
                                 __func__, __LINE__, ## x); }while(0)

#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#ifdef PRINT_INFO
#undef PRINT_INFO
#endif
#define PRINT_INFO(format,x...)   \
do{ printf(format, ## x); }while(0)

#ifdef DEBUG_LOG_SUPPORT
#ifdef PRINT_DEBUG
#undef PRINT_DEBUG
#endif
#define PRINT_DEBUG(format,x...)  \
do{ printf("func: %s line: %d info: " format,    \
                                 __func__, __LINE__, ## x); }while(0)
#else
#define PRINT_DEBUG(format,x...)  
#endif

#ifdef MAX_SIZE
#undef MAX_SIZE
#endif
#define MAX_SIZE 1024

#ifdef MSGQ_FILE_PATH
#undef MSGQ_FILE_PATH
#endif
#define MSGQ_FILE_PATH "."

#ifdef MSGQ_ID
#undef MSGQ_ID
#endif
#define MSGQ_ID 'a'

struct MsgFrame {
    int size;
    char buffer[MAX_SIZE];
};

#endif

