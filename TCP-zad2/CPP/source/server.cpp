#include "server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

server::server(int buffer_size, int no_connections){
    BSIZE = buffer_size;
    CONNECTIONS = no_connections;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {std::cerr << "opening the socket" <<std::endl; exit(1);}

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = 0;
    if(bind(sock, (struct sockaddr *) &serv, sizeof(serv)) == -1){
        std::cerr << "binding stream socket" <<std::endl;
        exit(2);
    }
    int length = sizeof(serv);
    if(getsockname(sock, (struct sockaddr *) &serv, (socklen_t *) &length) == -1){
        std::cerr << "getting socket name" <<std::endl;
    }
    std::cout << "Socket port " << ntohs(serv.sin_port) <<std::endl;
    listen(sock, CONNECTIONS);
}

int server::new_connection()
{
    char buf[BSIZE];
    int rval;
    int msgsock = accept(sock, (struct sockaddr *) 0, (socklen_t *) 0);
    if(msgsock == -1){
        std::cerr << "Socket did not recieve anything";
    } else {
        do
        {
            memset(buf, 0, sizeof(buf));
            if((rval = read(msgsock, buf, BSIZE)) == -1){
                std::cerr << "reading stream message failed" <<std::endl;
                exit(4);
            }
            if(rval == 0)
                std::cout << "ending connection" <<std::endl;
            else
                printf("-->%s\n", buf);
        }
        while(rval > 0);
        close(msgsock);
    }
    return 0;
}

server::~server()
{
    std::cerr << "closing socket " <<ntohs(serv.sin_port) <<std::endl;
    close(sock);
}
