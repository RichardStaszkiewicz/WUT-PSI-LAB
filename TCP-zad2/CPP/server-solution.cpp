#include "server.hpp"
#include <iostream>

using namespace std;

// ./server [buffer_size (exercise 1)] [connections]
// ./server [buffer_size (exercise 1)] [connections] [1] serwer dziala caly czas. Tylko zadanie 2.1
int main(int argc, char* argv[])
{
    int BUFFER_SIZE, NO_CONNECTIONS, CROSS_PLATFORM;
    if(argc > 1) BUFFER_SIZE = atoi(argv[1]);
    else BUFFER_SIZE = 512;
    if(argc > 2) NO_CONNECTIONS = atoi(argv[2]);
    else NO_CONNECTIONS = 5;
    if(argc > 3) CROSS_PLATFORM = atoi(argv[3]);
    else CROSS_PLATFORM = 0;

    if (CROSS_PLATFORM==1){
        std::cout << "----------Exercise 2.1-----------\n";
        server* zad1 = new server(BUFFER_SIZE, NO_CONNECTIONS);
        while (true){
            zad1->new_connection();
        }
        delete zad1;
    }

    else {

        // Exercise 1
        std::cout << "----------Exercise 2.1-----------\n";
        server* zad1 = new server(BUFFER_SIZE, NO_CONNECTIONS);
        zad1->new_connection();
        delete zad1;

        // Exercise 2
        std::cout << "\n\n----------Exercise 2.2-----------\n";
        server* zad2 = new server(5, NO_CONNECTIONS);
        zad2->new_connection();
        delete zad2;

        // Exercise 3
        std::cout << "\n\n----------Exercise 2.4-----------\n";
        server* zad3 = new server(BUFFER_SIZE, NO_CONNECTIONS, false);
        zad3->new_connection(10);
        delete zad3;

    }
    return 0;
}