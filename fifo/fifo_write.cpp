/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : fifo_write.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2021-01-26 init v1.0
* brief       : https://blog.csdn.net/ljianhui/article/details/10253345
* Others      :
********************************************************************************
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define BUFF_SIZE 1024

//char path_name[] = "~/hdd1/";

int main(int argc, char *argv[])
{
    int ret = 0, fd = 0;
    char buff[1024] = {0};

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ret = access(argv[1], F_OK);
    if (ret == -1) {
        ret = mkfifo(argv[1], 0664);
        if (ret == 0) {
            fprintf(stdout, "Create fifo named %s success.\n", argv[1]);
        } else {
            fprintf(stderr, "Create fifo named %s failed!\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    fd =open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Open fifo failed!\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        memset(buff, 0, BUFF_SIZE);
        fprintf(stdout, "input: ");
        fgets(buff, BUFF_SIZE, stdin);

        write(fd, buff, sizeof(buff));

        if (strncmp("end", buff, strlen(buff)-1) == 0) {
            close(fd);
            
            break;
        }
    }

    return 0;
}

