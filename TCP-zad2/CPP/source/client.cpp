#include "client.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

client::client(char* host_ip, char* server_port){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {std::cerr << "Could not load descriptor" <<std::endl; exit(1);}
    server.sin_family = AF_INET;
    hp = gethostbyname(host_ip);
    if(hp == (struct hostent *) 0) {std::cerr << "Unknown host" <<std::endl; exit(2);}
    memcpy((char*) &server.sin_addr, (char*) hp->h_addr, hp->h_length);
    server.sin_port = htons(atoi(server_port));
}

int client::send_TCP_message(const void* message)
{
    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) == -1){
        std::cerr << "Connection of socket failed" << std::endl; return 3;
    }
    int length = strlen((char*)message);
    if(write(sock, message, length) == -1){
        std::cerr << "Writing on socket failed" <<std::endl; return 4;
    }
    return 0;
}

client::~client()
{
    close(sock);
}
