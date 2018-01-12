#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <signal.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define __FAVOR_BSD
#include <arpa/inet.h>

#include "socket_server.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int HandleMessage(char *buf, int len)
{
    int rv = 0;
    SOCKET_SERVER_MSG_TYPE *pMsg;

    pMsg = (SOCKET_SERVER_MSG_TYPE *)buf;

    if(pMsg->startId != MESSAGE_START || len < (int)MSG_HEAD_LEN)
    {
        //it's not a correct message. return error
        return -1;
    }

    if(pMsg->dataLen != (len - MSG_HEAD_LEN))
    {
        //there is some issue in the content
        return -1;
    }

    switch(pMsg->msgId)
    {
        case MESSAGE_ID_HAPPY:
            printf(GREEN"I receive 1\n");
            break;
    }

    return rv;
}


int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    int socketfd;
    struct sockaddr_in myaddr;
    struct sockaddr_in client_addr;
    int length;
    int nbytes;
    char buf[101];
    int rv;


    //create communication channel for other application to send message
    if((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("SOCKET_SERVER: Fail to create socket!\n");
        exit(EXIT_FAILURE);
    }
    bzero ((char *)&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    myaddr.sin_port = htons(SOCKET_SERVER_PORT);

    if (bind(socketfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) <0)
    {
        perror("SOCKET_SERVER: Fail to bind socket!\n");
        exit(EXIT_FAILURE);
    }

    length = sizeof(client_addr);

    while(1)
    {
        FD_ZERO(&rfds);
        FD_SET(socketfd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 1;

        retval = select(socketfd + 1, &rfds, NULL, NULL, &tv);

        if(retval > 0)
        {
            if(FD_ISSET(socketfd, &rfds))
            {
                nbytes = recvfrom(socketfd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, (socklen_t *)&length);
                if(nbytes > 0)
                {
                    rv = HandleMessage(buf, nbytes);
                    *(int *)buf = rv;
                    sendto(socketfd, buf, sizeof(rv), 0, (struct sockaddr*)&client_addr, length);
                }
            }
        }
    }

    close(socketfd);

    return 0;
}
