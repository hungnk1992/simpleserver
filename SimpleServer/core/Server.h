#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

#define INPUT_BUFFER_SIZE 100 //test: 100 bytes of buffer
#define DEFAULT_PORT 9034

class Server
{
public:
    Server();
    Server(int port);
    Server(const Server& orig);
    virtual ~Server();
    
    struct Connector {
        uint16_t source_fd;
    };
    
    void shutdown();
    void init();
    void loop();

    //callback setters
    void onConnect(void (*ncc)(uint16_t fd));
    void onInput(void (*rc)(uint16_t fd, char *buffer));
    void onDisconnect(void (*dc)(uint16_t fd));

    uint16_t sendMessage(Connector conn, const char *messageBuffer);
    uint16_t sendMessage(Connector conn, char *messageBuffer);

private:
    //fd_set file descriptor sets for use with FD_ macros
    fd_set masterfds;
    fd_set tempfds;

    //unsigned integer to keep track of maximum fd value, required for select()
    uint16_t maxfd;

    //socket file descriptors
    int mastersocket_fd; //master socket which receives new connections
    int tempsocket_fd; //temporary socket file descriptor which holds new clients

    //client connection data
    struct sockaddr_storage client_addr;
    //server socket details
    struct sockaddr_in servaddr;
    //input buffer
    char input_buffer[INPUT_BUFFER_SIZE];

    char remote_ip[INET6_ADDRSTRLEN];
    //int numbytes;

    void (*newConnectionCallback) (uint16_t fd);
    void (*receiveCallback) (uint16_t fd, char *buffer);
    void (*disconnectCallback) (uint16_t fd);


    //function prototypes
    void setup(int port);
    void initializeSocket();
    void bindSocket();
    void startListen();
    void handleNewConnection();
    void recvInputFromExisting(int fd);
    uint16_t mSource_fd;

    //void *getInetAddr(struct sockaddr *saddr);


};