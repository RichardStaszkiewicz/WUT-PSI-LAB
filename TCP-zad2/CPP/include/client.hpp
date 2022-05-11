#ifndef CLIENT
#define CLIENT
#include <netinet/in.h>

class client
{
public:
    client(char* host_ip, char* server_port);
    int send_TCP_message(const void* message);
    ~client();
private:
    struct sockaddr_in server;
    int sock;
    struct hostent *hp;
};

#endif