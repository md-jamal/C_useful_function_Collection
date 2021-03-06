#include "network.h"

int make_socket ( uint16_t port, int type, const char * server_IP )
{
    int sock;
    struct hostent *    hostinfo = NULL;
    struct sockaddr_in  server_address;

    /* Create the socket. */
    sock = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    if (sock < 0) {
        perror ( "socket" );
        exit ( 1 );
    }

    /* Give the socket a name. */
    memset(&server_address, 0, sizeof(server_address));  
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons ( port );

    if ( type == SERVER_SOCKET ) {
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        if ( bind ( sock, ( struct sockaddr * ) &server_address, sizeof ( server_address ) ) < 0 ) {
            perror ( "bind" );
            exit ( 1 );
        }

        if ( listen(sock, MAXPENDING) < 0 ) {
            printf("listen() failed");
        }
    } else if ( type == CLIENT_SOCKET ) {
        server_address.sin_addr.s_addr = inet_addr(server_IP);

        /* Establish the connection to the server */
        if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            printf("connect() failed\n");
        }
    }
    return sock;
}

void close_socket (int socket)
{
    close (socket);
}

char * clean_data( const char * data )
{
    int count;
    char * ptr_data      = NULL;
    char * result_data   = NULL;
    char * temp_ptr_data = NULL;
    int len;
    int write_info, ifone;

    ptr_data = strstr (data, DIVIDER);
    ptr_data =& ptr_data[strlen(DIVIDER)];

    temp_ptr_data = malloc ( strlen (ptr_data) );
    strcpy (temp_ptr_data, ptr_data);
    result_data = (char *) strsep (&temp_ptr_data, DIVIDER);
    printf ("%i, %i, %s", strlen (data), strlen (ptr_data), result_data);
    return result_data;
}

void send_data ( int socket, const char * data )
{
    int sent_bytes, all_sent_bytes;
    int err_status;
    int sendstrlen;

    sendstrlen = strlen ( data );
    all_sent_bytes = 0;

    sent_bytes = send ( socket, data, sendstrlen, 0 );
    all_sent_bytes = all_sent_bytes + sent_bytes;
    printf ("\t !!! Sent data: %s --- \n", data);
}
