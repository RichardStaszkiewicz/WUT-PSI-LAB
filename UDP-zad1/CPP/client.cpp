#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

#define DATA "LoremIpsumLoremIpsumLoremIpsum"

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

    if(sendto(sock, DATA, sizeof DATA, 0, (struct sockaddr*) &name, sizeof name) == -1){
        std::cerr << "Sending datagram message" <<std::endl;
    }
    close(sock);
    exit(0);
}