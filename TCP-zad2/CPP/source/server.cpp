#include "server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <chrono>

server::server(int buffer_size, int no_connections, bool interact/*=true*/){
    interactive = interact;
    BSIZE = buffer_size;
    CONNECTIONS = no_connections;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {std::cerr << "opening the socket" <<std::endl; exit(1);}

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5000);
    if(bind(sock, (struct sockaddr *) &serv, sizeof(serv)) == -1){
        std::cerr << "binding stream socket" <<std::endl;
        exit(2);
    }
    int length = sizeof(serv);
    if(getsockname(sock, (struct sockaddr *) &serv, (socklen_t *) &length) == -1){
        std::cerr << "getting socket name" <<std::endl;
    }
    if(interactive) std::cout << "INFO: Opened socket port " << ntohs(serv.sin_port) <<std::endl;
    if(interactive) std::cout << "INFO: Server buffer size: " << BSIZE << "B" <<std::endl;
    listen(sock, CONNECTIONS);
    if(interactive) std::cout << "INFO: Server connection limit: " << CONNECTIONS  <<std::endl;
}

int server::new_connection(int milliseconds_delay)
{
    char buf[BSIZE];
    int rval;
    if(interactive) std::cout << "INFO: Initiating new connection..." << std::endl;
    int msgsock = accept(sock, (struct sockaddr *) 0, (socklen_t *) 0);
    if(msgsock == -1){
        std::cerr << "Socket did not recieve anything";
    } else {
        int payload = 0;
        do
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_delay));
            memset(buf, 0, sizeof(buf));
            if((rval = read(msgsock, buf, BSIZE)) == -1){
                std::cerr << "reading stream message failed" <<std::endl;
                exit(4);
            }
            if(rval == 0)
                {if(interactive) std::cout << "INFO: ending connection..." <<std::endl;}
            else{
                if(interactive) printf("MESSAGE RECIEVED: [%dB] %.*s\n", rval, rval, buf);
                payload += rval;
            }
        }
        while(rval > 0);
        std::cout << "Read " << payload << "B of data during the connection...\n";
        close(msgsock);
    }
    return 0;
}

server::~server()
{
    std::cerr << "closing port " <<ntohs(serv.sin_port) <<std::endl;
    close(sock);
}
