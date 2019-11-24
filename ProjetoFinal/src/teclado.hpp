#ifndef TECLADO_HPP
#define TECLADO_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

void threadfun (char *keybuffer, int *control, int *connection_fd, int *socket_fd, struct sockaddr_in *client);

class Teclado {
  private:
    char ultima_captura;
    int rodando;
    int connection_fd;
    int socket_fd;
    std::thread kb_thread;
    struct sockaddr_in server;
    struct sockaddr_in client;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};

#endif
