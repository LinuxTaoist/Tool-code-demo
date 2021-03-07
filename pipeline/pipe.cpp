/*
********************************************************************************
* Copyright (C) 2021, xiang.D <dx_65535@163.com>.
* All right reserved.
*
* File Name   : pipe.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2021-01-26 init v1.0
* brief       : https://blog.csdn.net/ljianhui/article/details/10253345
* Others      :
********************************************************************************
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
   int pipe_fd[2];
   pid_t child_id;
   char buf;

   if (argc != 2) {
       fprintf(stderr, "Usage: %s <string>\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   if (pipe(pipe_fd) == -1) {
       perror("pipe");
       exit(EXIT_FAILURE);
   }

   child_id = fork();
   if (child_id == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (child_id == 0) {            /* Child reads from pipe */
       close(pipe_fd[1]);          /* Close unused write end */

       while (read(pipe_fd[0], &buf, 1) > 0) {
           write(STDOUT_FILENO, &buf, 1);
           write(STDOUT_FILENO, " ", 1);
       }
       write(STDOUT_FILENO, "\n", 1);
       close(pipe_fd[0]);
       _exit(EXIT_SUCCESS);

   } else {                        /* Parent writes argv[1] to pipe */
       close(pipe_fd[0]);          /* Close unused read end */
       write(pipe_fd[1], argv[1], strlen(argv[1]));
       close(pipe_fd[1]);          /* Reader will see EOF */
       wait(NULL);                 /* Wait for child */
       exit(EXIT_SUCCESS);
   }

}
