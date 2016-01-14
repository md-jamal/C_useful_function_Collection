#include "network.h"

int accept_connection(int server_socket)
{
    int client_socket;                          /* Socket descriptor for client */
    struct sockaddr_in client_address;          /* Client address */
    unsigned int client_length;                 /* Length of client address data structure */

    /* Set the size of the in-out parameter */
    client_length = sizeof(client_address);

    /* Wait for a client to connect */
    if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_length)) < 0) {
        printf("accept() failed");
    }

    /* client_socket is connected to a client! */
    printf("Handling client %s\n", inet_ntoa(client_address.sin_addr));

    return client_socket;
}

void handle_client (int client_socket)
{
    char buffer [BUFFSIZE];           /* Buffer for incomming data */
    int msg_size;                     /* Size of received message  */
    int bytes, all_bytes;

    do {
        alarm (60);
        msg_size = read (client_socket, buffer, BUFFSIZE);
        alarm (0);

        if ( msg_size <= 0 ) {
            printf ( " %i ", msg_size );
            printf ( "End of data\n" );
        }
    } while ( msg_size > 0 );
    printf ("Data received: %s", buffer);
    bytes = 0;
}

int main()
{
    int clnt_sock;
    int sock = make_socket(ADRESS_PORT, SERVER_SOCKET, "none");
    clnt_sock = accept_connection (sock);
    handle_client(clnt_sock);
    close_socket(sock);
    return 0;
}
