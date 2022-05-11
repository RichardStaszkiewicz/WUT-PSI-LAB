#include "server.hpp"
#include <iostream>

using namespace std;

// ./server [buffer_size] [connections]
int main(int argc, char* argv[])
{
    int BUFFER_SIZE, NO_CONNECTIONS;
    if(argc > 1) BUFFER_SIZE = atoi(argv[1]);
    else BUFFER_SIZE = 1024;
    if(argc > 2) NO_CONNECTIONS = atoi(argv[2]);
    else NO_CONNECTIONS = 5;

    // Zadanie 1
    server* zad1 = new server(BUFFER_SIZE, NO_CONNECTIONS);
    zad1->new_connection();
    delete zad1;
    return 0;
}