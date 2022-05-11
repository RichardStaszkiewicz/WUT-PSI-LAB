#ifndef SERVER
#define SERVER

#include <netinet/in.h>

class server
{
public:
    server(int buffer_size, int no_connections, bool interact=true);
    int new_connection(int milliseconds_delay = 0);
    ~server();
private:
    int sock;
    struct sockaddr_in serv;
    int BSIZE, CONNECTIONS;
    bool interactive;
};

#endif