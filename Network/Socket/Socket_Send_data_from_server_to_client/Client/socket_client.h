#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#define SOCKET_CLIENT_MSGQ_ID 3366

#define MESSAGE_ID_CONFIG_UPDATE 2

#define MESSAGE_START 0xa52d

#define SOCKET_CLIENT_PORT 22724

typedef struct SOCKET_CLIENT_MSG_TYPE
{
    unsigned short startId;
    unsigned short msgId;
    unsigned short dataLen;
    unsigned short pad;
    char data[100];
} SOCKET_CLIENT_MSG_TYPE;

#define MSG_HEAD_LEN (sizeof(SOCKET_CLIENT_MSG_TYPE)-sizeof(char [100]))
#endif


