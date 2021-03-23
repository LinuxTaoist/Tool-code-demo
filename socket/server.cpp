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
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "common.h"

int main(int argc, char *argv[])
{
    char rec_buf[RECV_LEN_MAX] = {0}, snd_buf[] = "ok";
    int serv_sock, sockfd, ret = 0, len = 0;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t cli_addr_len;

    unlink(FILE_NAME);

    /* Create socket */
    serv_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serv_sock < 0) {
        PRINT_ERR("socket failed! errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    memset(&serv_addr, 0x00, sizeof(struct sockaddr_un));
    strcpy(serv_addr.sun_path, FILE_NAME);
    serv_addr.sun_family = AF_UNIX;
    ret = bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        PRINT_ERR("bind failed!\n errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    ret = listen(serv_sock, SOCK_QUEUE_MAX);
    if (ret < 0) {
        PRINT_ERR("listen failed!\n errno = %d(%s)\n", errno, strerror(errno));
        goto exit;
    }

    PRINT_DEBUG("Will enter accept!\n");

    cli_addr_len = sizeof(cli_addr);
    /* loop: Server keeps running*/
    while (1) {
        sockfd = accept(serv_sock, (struct sockaddr*)&cli_addr, &cli_addr_len);
        if (sockfd < 0) {
            PRINT_ERR("accept failed! errno = %d(%s)\n", errno, strerror(errno));
        }

        PRINT_INFO("Server is waiting for client data...\n");

        /* loop: Connection status, processing client messages */
        while (1) {
            len = read(sockfd, rec_buf, RECV_LEN_MAX);
            if (len < 0) {
                PRINT_ERR("read error!\n");
                break;
            } else if (len == 0){
                /* Read to the end of the file */
                PRINT_ERR("EOF!\n");
                break;
            } else {
                PRINT_INFO("[Receive] %s\n", rec_buf);
            }

            ret = write(sockfd, snd_buf, strlen(snd_buf));
            if (ret < 0) {
                PRINT_ERR("ack failed! errno = %d(%s)\n", errno, strerror(errno));
                break;
            }
        }
        close(sockfd);
    }
    close(serv_sock);
    serv_sock = -1;

exit:
    if (serv_sock >= 0) {
        close(serv_sock);
    }

    return 0;
}
