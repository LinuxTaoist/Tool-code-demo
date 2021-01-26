/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : write.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2021-01-26 init v1.0
* brief       :
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
    char buffer[DATA_SIZE+1] = {0};
    void *shm = NULL;
    struct ShmData *pShareData = NULL;

    shmid = shmget((key_t)SHM_NAME, sizeof(struct ShmData), 0666|IPC_CREAT);
    if (shmid == -1) {
        printf("shmget failed!\n");
        exit(0);
    }

    shm = shmat(shmid, (void*)0, 0);
    if (shm == (void*)-1) {
        printf("shmat failed!\n");
        exit(0);
    }
    printf("Memory attached at %p\n", shm);

    pShareData = (struct ShmData *)shm;
    //pShareData->flag = 0;

    while (running) {
        while (pShareData->flag == 1) {
            sleep(1);
            printf("Waiting...\n");
        }

        printf("Input data: ");
        fgets(buffer, DATA_SIZE, stdin);
        strncpy(pShareData->data, buffer, DATA_SIZE);
        pShareData->flag = 1;

        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }

    if (shmdt(shm) == -1) {
        printf("shmdt failed!\n");
        exit(0);
    }
    sleep(2);

    return 0;
}
