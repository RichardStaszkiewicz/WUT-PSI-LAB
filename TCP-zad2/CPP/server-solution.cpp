#include "server.hpp"
#include <iostream>

using namespace std;

// ./server [buffer_size (exercise 1)] [connections]
int main(int argc, char* argv[])
{
    int BUFFER_SIZE, NO_CONNECTIONS;
    if(argc > 1) BUFFER_SIZE = atoi(argv[1]);
    else BUFFER_SIZE = 1024;
    if(argc > 2) NO_CONNECTIONS = atoi(argv[2]);
    else NO_CONNECTIONS = 5;

    // Exercise 1
    std::cout << "----------Exercise 1-----------\n";
    server* zad1 = new server(BUFFER_SIZE, NO_CONNECTIONS);
    zad1->new_connection();
    delete zad1;

    // Exercise 2
    std::cout << "\n\n----------Exercise 2-----------\n";
    server* zad2 = new server(5, NO_CONNECTIONS);
    zad2->new_connection();
    delete zad2;

    return 0;
}