#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int serverSocket;
    int clientSocket;
    struct sockaddr_in address;
    char buffer[100];
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
    bind(
        serverSocket,
        (struct sockaddr *)&address,
        sizeof(address)
    );
    listen(serverSocket, 5);
    printf("serveur en attente....\n");
    clientSocket = accept(
        serverSocket,
        NULL,
        NULL
    );
    read(clientSocket, buffer, sizeof(buffer));
    printf("Message recu : %s\n", buffer);
    close(clientSocket);
    close(serverSocket);
    return 0;
}
