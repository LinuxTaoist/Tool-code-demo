/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : client.cpp
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
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    int signo = 0;
    char mode[1] = {0};

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "1: SIGUSR1\n");
    fprintf(stdout, "2: SIG_TEST1\n");
    fprintf(stdout, "3: default\n");
    while (1) {
        signo = 0;
        fprintf(stdout, "Select signal to send %s: ", argv[1]);
        scanf("%s", mode);
        switch(mode[0]) {
          case '1':
            signo = SIGUSR1;
            break; 
          case '2':
            signo = SIG_TEST1;
            break;
          default:
            signo = SIG_DEFAULT;
            break;
        }
        //fprintf(stdout, "mode: %d %d\n", signo, SIG_DEFAULT);
        kill(atoi(argv[1]), signo);
    }
    return 0;
}

