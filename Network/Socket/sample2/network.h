#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>

#define ADRESS_PORT           10203
#define ADRESS_IP             "127.0.0.1"
#define MAXPENDING            5
#define BUFFSIZE              21

#define SERVER_SOCKET         1
#define CLIENT_SOCKET         0

#define TRUE                  1
#define FALSE                 0
#define START                 11
#define DIVIDER               ":"
