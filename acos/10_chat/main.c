#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define MAX_NUMBER_OF_USERS 2

enum EMode
{
    CLIENT, SERVER, OTHER;
};

static EMove getMode(char* mode)
{
    if (strcmp(mode, "client") == 0) {
        return EMode::CLIENT;
    } else if (strcmp(mode, "server") == 0) {
        return EMode::SERVER;
    } else {
        return EMode::OTHER;
    }
}

static void parseInput(int argc, char** argv, 
                       EMode* mode, int* port, struct in_addr* addr)
{
    *mode = getMode(argv[1]);
    *port = atoi(argv[2]);
    if (argc > 3) {
        *addr = inet_aton(argv[2]);
    }
}

static void client(int port, struct in_addr inAddress)
{
    // to be written
}

static void server(int port)
{
   int listener; 
   struct sockaddr_in addr;
   char message[1000];

   // create listener non-blocking socket
   listener = socket(AF_INET, SOCK_STREAM, 0);
   if (listener < 0) {
       perror("listener");
       return 1;
   }
   fcntl(listener, F_SETFL, O_NONBLOCK); // set socket not to block

   // binding listener socket
   addr.sin_family = AF_INET;
   addr.sin_port = port;
   addr.sin_addr.s_addr = INADDR_ANY;
   if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
       perror("bind");
       return 1;
   }

   listen(listener, MAX_NUMBER_OF_USERS);

   // TBD:
   // - store all connected clients in some data structure
   // - implement multiplexing of requests

} 

int main(int argc, char** argv)
{
    int port;
    struct in_addr addr;
    EMode mode;

    parseInput(argc, argv, &mode, &port, &addr);

    switch (mode) {
    EMode::CLIENT:
        client(port, addr);
        break;
    EMode::SERVER:
        server(port);
        break;
    EMode::OTHER:
        assert(false && "Only client & server are available as modes");
    }

    return 0;
}
