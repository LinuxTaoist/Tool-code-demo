/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : server.cpp
* Author      :
* Version     : V1.0
* Description :
* Journal     : 2021-03-06 init v1.0
* Brief       : Blog address: https://blog.csdn.net/qq_38750572?spm=1001.2014.3001.5343
* Others      :
********************************************************************************
*/

#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "common.h"

void SignalHandler(int sig)
{
    fprintf(stdout, "Receive signal: ");
    switch(sig) {
      case SIGUSR1:
        fprintf(stdout, "SIGUSR1\n");
        break;
      case SIG_TEST1:
        fprintf(stdout, "SIG_TEST1\n");
        break;
      default:
        fprintf(stdout, "default\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    fprintf(stdout, "Pid: %d\n", getpid());
    signal(SIGUSR1, SignalHandler);
    signal(SIG_TEST1, SignalHandler);
    signal(SIG_DEFAULT, SignalHandler);
    while(1);

    return 0;
}
