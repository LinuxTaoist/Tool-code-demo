/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : server.cpp
* Author      :
* Version     : V1.0
* Description :
* Journal     : 2021-03-21 init v1.0
* Brief       : Blog address: https://blog.csdn.net/qq_38750572?spm=1001.2014.3001.5343
* Others      :
********************************************************************************
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream> 
#include <errno.h>
#include <string.h>
#include "common.h"

int main(int argc, char *argv[])
{
    int msg_id, key, ret = 0;
    struct MsgFrame msg_recv = {0, {0}};

    /* Obtain the standard key according to the file path */
    key = ftok(MSGQ_FILE_PATH, MSGQ_ID);
	if (key < 0)
	{
		PRINT_ERR("ftok failed! errno = %d(%s)\n", errno, strerror(errno));
		goto exit;
	}

    msg_id = msgget(key, IPC_EXCL);
    if (msg_id < 0) {
        PRINT_ERR("msgget failed! errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    do {
        memset(msg_recv.buffer, 0x11, sizeof(struct MsgFrame));
        ret = msgrcv(msg_id,(void*)&msg_recv,sizeof(struct MsgFrame),0,0);
        if (ret != -1) {
            PRINT_INFO("Receive: %s, len: %d\n", msg_recv.buffer, msg_recv.size);
        }
    } while (1);

exit:
    return 0;
}
