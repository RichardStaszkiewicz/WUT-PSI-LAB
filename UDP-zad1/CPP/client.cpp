#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>

#define DATA "LoremIpsumLoremIpsumLoremIpsum"
#define BUFSIZE 100000

// client [hostname eg. ip] [servport] [mode]
int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in name;
    struct hostent *hp;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1) {
        std::cerr << "Opening socket failed" <<std::endl;
        exit(1);
    }

    hp = gethostbyname(argv[1]);
    if(hp == (struct hostent*) 0){
        std::cerr << "Host name not found" <<std::endl;
        exit(2);
    }

    memcpy((char*) &name.sin_addr, (char*) hp->h_addr, hp->h_length);
    name.sin_family = AF_INET;
    name.sin_port = htons( atoi( argv[2] ));

    if(atoi(argv[3]) == 1){
        char buffer[1024];
        for(int i = 0; i < 10; i++){
            if(sendto(sock, DATA, sizeof DATA, 0, (struct sockaddr*) &name, sizeof name) == -1){
                std::cerr << "Sending datagram message" <<std::endl;
            }
            socklen_t size = sizeof(name);
            recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&name, &size);
            printf("[+][%d]Data recv: %s\n", i, buffer);
            bzero(buffer, 1024);
        }
    }

    if(atoi(argv[3]) == 2){
        char buf[BUFSIZE];
        buf[0] = 'X';
        int size = 1;
        while(sendto(sock, buf, size, 0, (struct sockaddr*) &name, sizeof name) != -1){
            size++;
            if(size % 5000 == 0)
                std::cerr << "Transmition cap: " << size << "B...\n";
        }
        std::cerr << "Transmition denied at: " << size << "B\n";
    }

    if(atoi(argv[3]) == 3){
        char buf[1] = {'\0'};
        sendto(sock, buf, 1, 0, (struct sockaddr*) &name, sizeof name);
        std::cerr << "Kill signal transmitted...\n";
    }

    close(sock);
    exit(0);
}