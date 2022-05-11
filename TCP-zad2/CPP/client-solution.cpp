#include "client.hpp"
#include <iostream>

using namespace std;

// ./client [SERVER_PORT] [HOST_IP]
int main(int argc, char* argv[])
{
    char *HOST_IP, *SERVER_PORT;
    if(argc > 1) SERVER_PORT = argv[1];
    else SERVER_PORT = (char*)"5000";
    if(argc > 2) HOST_IP = argv[2];
    else HOST_IP = (char*)"127.0.0.1";

    client *zad1 = new client(HOST_IP, SERVER_PORT);
    zad1->send_TCP_message((char*)"LOREM IPSUM LOREM IPSUM");
    return 0;
}