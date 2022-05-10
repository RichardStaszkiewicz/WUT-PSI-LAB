#ifndef SERVER
#define SERVER

#include <netinet/in.h>

class server
{
public:
    server(int buffer_size, int no_connections);
    int new_connection();
    ~server();
private:
    int sock;
    struct sockaddr_in serv;
    int BSIZE, CONNECTIONS;
};

#endif