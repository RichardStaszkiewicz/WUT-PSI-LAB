#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>


#define MAXSIZE 1024

// ./server [port] [mode]
int main(int argc, char *argv[])
{
    int sock, len;
    struct sockaddr_in name, client_addr;
    char buffer[MAXSIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        std::cerr << "Couldn't open the socket" <<std::endl;
        exit(1);
    }

    memset(&name, '\0', sizeof name);
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port = htons(atoi(argv[1]));
    if(bind(sock, (struct sockaddr*) &name, sizeof name) == -1){
        std::cerr << "Couldn't bind datagram socket" <<std::endl;
        exit(2);
    }


    if(atoi(argv[2]) == 1){
        while(true){
            bzero(buffer, MAXSIZE);
            socklen_t addr_size = sizeof(client_addr);
            recvfrom(sock, buffer, MAXSIZE, 0, (struct sockaddr*)&client_addr, &addr_size);
            printf("[+]Data recv: %s\n", buffer);

            if(buffer[0] == '\0') break;

            bzero(buffer, MAXSIZE);
            strcpy(buffer, "Welcome to the UDP Server.");
            sendto(sock, buffer, MAXSIZE, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
            printf("[+]Data send: %s\n", buffer);
        }
    } if(atoi(argv[2]) == 2){
        while(true){
            bzero(buffer, MAXSIZE);
            socklen_t addr_size = sizeof(client_addr);
            recvfrom(sock, buffer, MAXSIZE, 0, (struct sockaddr*)&client_addr, &addr_size);
            if(buffer[0] == '\0') break;
        }
    }
    close(sock);
    // uwalnianie deskryptora przy twardym wyjściu?
    return 0;
}