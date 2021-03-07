/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : read.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2021-01-26 init v1.0
* brief       : https://blog.csdn.net/ljianhui/article/details/10253345
* Others      :
********************************************************************************
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "common.h"

int main(int argc, char *argv[])
{
    int shmid, running = 1;
    void *shm = NULL;
    struct ShmData *pShareData = NULL;

    shmid = shmget((key_t)SHM_NAME, sizeof(struct ShmData), 0666|IPC_CREAT);
    if (shmid == -1) {
        printf("shmget failed!\n");
        exit(0);
    }

    shm = shmat(shmid, 0, 0);
    if (shm == (void*)-1) {
        printf("shmat failed!\n");
        exit(0);
    }
    printf("Memory attached at %p\n", shm);

    pShareData = (struct ShmData *)shm;
    pShareData->flag = 0;

    while (running) {
        if (pShareData->flag) {
            printf("The memery data: %s", pShareData->data);
            sleep(rand() % 3);
            pShareData->flag = 0;

            if (!strncmp(pShareData->data, "end", 3)) {
                running = 0;
            }

        } else {
            sleep(1);
        }
    }

    printf("Over!\n");
    if (shmdt(shm) == -1) {
        printf("shmdt failed!\n");
        exit(0);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("shmctl failed!\n");
        exit(0);
    }

    return 0;
}
