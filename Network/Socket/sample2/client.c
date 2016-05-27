#include "network.h"

int main()
{
    int sock = make_socket(ADRESS_PORT, CLIENT_SOCKET, "127.0.0.1");
    send_data (sock, "Some data to be sent");
    close_socket(sock);
    return 0;
}
