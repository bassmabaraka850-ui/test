#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main()
{
    int sock;
    struct sockaddr_in address;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(
        sock,
        (struct sockaddr *)&address,
        sizeof(address)
    );
    write(sock, "Bonjour serveur", 16);
    close(sock);
    return 0;
}
