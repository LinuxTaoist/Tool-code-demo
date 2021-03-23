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
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "common.h"

int main(int argc, char *argv[])
{
    char snd_buf[SND_LEN_MAX] = "hello world", recv_buf[RECV_LEN_MAX] = {0};
    int ret, sock = -1;
    struct sockaddr_un cli_addr;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        PRINT_ERR("socket failed! errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    strcpy(cli_addr.sun_path, FILE_NAME);
    cli_addr.sun_family = AF_UNIX;
    ret = connect(sock, (struct sockaddr*)&cli_addr, SUN_LEN(&cli_addr));
    if(ret < 0) {
        PRINT_ERR("connect failed! errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    ret = write(sock, snd_buf, strlen(snd_buf));
    if (ret < 0) {
        PRINT_ERR("write failed! errno = %d(%s)\n", errno, strerror(errno));
    } else {
        PRINT_INFO("[send] %s\n", snd_buf);
    }

    ret = read(sock, recv_buf, RECV_LEN_MAX);
    if (read < 0) {
        PRINT_ERR("not receive ack of server!\n");
    } else {
        PRINT_INFO("Receive ack (%s)\n", recv_buf);
    }

    close(sock);
    sock = -1;

exit:
    if (sock > 0) {
        close(sock);
    }

    return 0;
}
