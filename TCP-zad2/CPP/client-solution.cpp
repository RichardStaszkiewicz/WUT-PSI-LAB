#include "client.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#define data "LOREM IPSUM LOREM IPSUM"

// ./client [SERVER_PORT] [HOST_IP]
// ./client [SERVER_PORT] [HOST_IP] [1] - EXERCISE 1 ONLY
int main(int argc, char* argv[])
{
    char *HOST_IP, *SERVER_PORT, EX1_ONLY;
    if(argc > 1) SERVER_PORT = argv[1];
    else SERVER_PORT = (char*)"5000";
    if(argc > 2) HOST_IP = argv[2];
    else HOST_IP = (char*)"127.0.0.1";
    if(argc > 3) EX1_ONLY = atoi(argv[3]);
    else EX1_ONLY = 0;

    // Exercise 1
    std::cout << "----------Exercise 1-----------\n";
    client *zad1 = new client(HOST_IP, SERVER_PORT);
    zad1->send_TCP_message(data);
    delete zad1;
    this_thread::sleep_for(std::chrono::seconds(3));

    if (EX1_ONLY == 0){
        // Exercise 2
        std::cout << "\n\n----------Exercise 2-----------\n";
        client *zad2 = new client(HOST_IP, SERVER_PORT);
        zad2->send_TCP_message(data);
        delete zad2;

        this_thread::sleep_for(std::chrono::seconds(3));

        // Exercise 3
        std::cout << "\n\n----------Exercise 3-----------\n";
        char bigdata[1000];
        for(int i = 0; i < 1000; i++) bigdata[i] = 'X';

        client *zad3 = new client(HOST_IP, SERVER_PORT);
        zad3->send_TCP_message((const void*) &bigdata, true, 5000);
        delete zad3;
    }    
    return 0;
}