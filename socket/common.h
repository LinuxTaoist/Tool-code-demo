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

#ifdef filename
#undef filename
#endif
#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#ifdef PRINT_INFO
#undef PRINT_INFO
#endif
#define PRINT_INFO(format,x...)   \
do{ printf(format, ## x); }while(0)

#ifdef PRINT_WARN
#undef PRINT_WARN
#endif
#define PRINT_WARN(format,x...)    \
do{ printf( "[WARN] [%s:%d] [%s] info: " format,  \
                     filename(__FILE__), __LINE__, __func__, ## x); }while(0)

#ifdef PRINT_ERR
#undef PRINT_ERR
#endif
#define PRINT_ERR(format,x...)    \
do{ printf( "[ERROR] [%s:%d] [%s] info: " format,    \
                        filename(__FILE__), __LINE__, __func__, ## x); }while(0)

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

#ifdef FILE_NAME
#undef FILE_NAME
#endif
#define FILE_NAME "/tmp/linux-sysprop"

#ifdef SOCK_QUEUE_MAX
#undef SOCK_QUEUE_MAX
#endif
#define SOCK_QUEUE_MAX 5

#ifdef RECV_LEN_MAX
#undef RECV_LEN_MAX
#endif
#define RECV_LEN_MAX 1024

#ifdef SND_LEN_MAX
#undef SND_LEN_MAX
#endif
#define SND_LEN_MAX 1024

#endif

