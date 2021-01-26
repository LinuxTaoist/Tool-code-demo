/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : common.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2021-01-26 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef  DATA_SIZE
#undef  DATA_SIZE
#endif
#define DATA_SIZE 2048

#ifdef  SHM_NAME
#undef  SHM_NAME
#endif
#define SHM_NAME 0x1234

struct ShmData {
    int  flag;
    char data[DATA_SIZE];
};

#endif //__COMMON_H__
