#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket_client.h"

int SendToTm(unsigned short msgId, char *pData, int len, int timeout)
{
    int socketfd;
    struct sockaddr_in servaddr;
    int length;
    SOCKET_CLIENT_MSG_TYPE msg;
    int nbytes;
    fd_set rfds;
    struct timeval tv;
    int retval;
    int rv = 1;

    if((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -100;
    }

    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SOCKET_CLIENT_PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    length = sizeof(servaddr);

    msg.startId = MESSAGE_START;
    msg.msgId = msgId;
    msg.dataLen = len;
    if(len > 0)
    {
        memcpy(msg.data, pData, len);
    }

    if (sendto(socketfd, &msg, MSG_HEAD_LEN + msg.dataLen, 0, (struct sockaddr*)&servaddr, length) == -1)
    {
        close(socketfd);
        return -100;
    }

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(socketfd, &rfds);

    retval = select(socketfd + 1, &rfds, NULL, NULL, &tv);

    if(retval > 0)
    {
        if(FD_ISSET(socketfd, &rfds))
        {
            nbytes = recvfrom(socketfd, &rv, sizeof(rv), 0, (struct sockaddr*)&servaddr, (socklen_t *)&length);
            if(nbytes > 0)
            {
                close(socketfd);
                return rv;
            }
        }
    }

    close(socketfd);
    return rv;
}

int main(int argc,char **argv)
{
    int __attribute__ ((unused)) rv;
    unsigned short __attribute__ ((unused)) id;

    if(argc > 1)
    {
        id = (unsigned short)atol(argv[1]);
        rv = SendToTm(atol(argv[1]), NULL, 0, 0);
    }

    return 0;
}

