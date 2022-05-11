#include "client.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <chrono>

client::client(char* host_ip, char* server_port, bool interact/*=true*/){
    interactive = interact;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {std::cerr << "Could not load descriptor" <<std::endl; exit(1);}
    server.sin_family = AF_INET;
    hp = gethostbyname(host_ip);
    if(hp == (struct hostent *) 0) {std::cerr << "Unknown host" <<std::endl; exit(2);}
    memcpy((char*) &server.sin_addr, (char*) hp->h_addr, hp->h_length);
    server.sin_port = htons(atoi(server_port));
}

int client::send_TCP_message(const void* message, bool flood, int stop)
{
    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) == -1){
        std::cerr << "Connection to socket failed" << std::endl; return 3;
    }
    int length = strlen((char*)message);
    if(flood)
    {
        if(interactive) std::cout << "Started poking with " << length << "B of data...\n";
        int average = 0;
        for(int i = 1; i <= stop; i++){
            auto begin = std::chrono::high_resolution_clock::now();
            if(write(sock, message, length) == -1){
                std::cerr << "Writing on socket failed" <<std::endl; return 4;}
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            if((i % 500 == 0) && interactive) std::cout << "INFO: Poke number " << i <<std::endl;
            if((elapsed.count() > 5*(average/i)) && interactive && i > 100) std::cout << "INFO: Blocked for " << elapsed.count() << "ms\n";
            else average += elapsed.count();
        }
    }
    else{
        if(write(sock, message, length) == -1){
        std::cerr << "Writing on socket failed" <<std::endl; return 4;
        }
        if(interactive) std::cout << "INFO: Send Message: [" << length << "B] " << (char*)message <<std::endl;
    }
    return 0;
}

client::~client()
{
    if(interactive) std::cout << "INFO: Closing Client socket..." <<std::endl;
    close(sock);
}
