/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : client.cpp
* Author      :
* Version     : V1.0
* Description :
* Journal     : 2021-03-19 init v1.0
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
    struct MsgFrame msg_buf = {0, {0}};

    /* Obtain the standard key according to the file path */
    key = ftok(MSGQ_FILE_PATH, MSGQ_ID);
	if (key < 0)
	{
		PRINT_ERR("ftok failed! errno = %d(%s)\n", errno, strerror(errno));
		goto exit;
	}

    msg_id = msgget(key, IPC_CREAT|0666);
    if (msg_id < 0) {
        PRINT_ERR("msgget failed! errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    do {
        memset(&msg_buf, 0x00, sizeof(msg_buf));
        ret = scanf("%s", msg_buf.buffer);
        if (ret == EOF) {
            PRINT_ERR("scanf failed! errno = %d(%s)\n", errno, strerror(errno));
            goto exit;
        }
        msg_buf.size = strlen(msg_buf.buffer);

        ret = msgsnd(msg_id, &msg_buf, sizeof(struct MsgFrame), IPC_NOWAIT);
        if (ret < 0) {
            PRINT_ERR("msgnd failed! errno = %d(%s)\n", errno, strerror(errno));
            goto exit;
        }

    } while (strncmp(msg_buf.buffer, "end", msg_buf.size) != 0);

exit:
    ret = msgctl(msg_id, IPC_RMID, 0);
    if (ret < 0) {
        PRINT_ERR("msgctl failed! errno = %d(%s)\n", errno, strerror(errno));
    }

    return 0;
}
