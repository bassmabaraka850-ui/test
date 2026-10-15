#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

int main()
{
    int serverSocket;
    int clientSocket;
    int sock;
    int opt = 1;
    struct sockaddr_in address;
    char buffer[100];

    /* ===== SERVER : socket + bind + listen (9bl fork) ===== */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    listen(serverSocket, 5);
    printf("[serveur] en attente....\n");
    fflush(stdout);

    pid_t pid = fork();

    if (pid == 0)
    {
        /* ===== CLIENT (process fils) ===== */
        close(serverSocket);
        struct sockaddr_in addr;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8080);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        connect(sock, (struct sockaddr *)&addr, sizeof(addr));
        write(sock, "Bonjour serveur", 16);
        printf("[client] message envoye\n");
        close(sock);
        return 0;
    }

    /* ===== SERVER (process pere) ===== */
    clientSocket = accept(serverSocket, NULL, NULL);
    ssize_t n = read(clientSocket, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("[serveur] Message recu : %s\n", buffer);
    close(clientSocket);
    close(serverSocket);
    wait(NULL);
    return 0;
}
