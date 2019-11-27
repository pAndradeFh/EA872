/*
	Paulo Roberto Andrade Filho - PROJETO FINAL. RA156951
*/
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <ncurses.h>

#include "audio.hpp"
#include "comida.hpp"
#include "player.hpp"
#include "gameController.hpp"
#include "fisica.hpp"
#include "tela.hpp"

#define WIDTH 50
#define HEIGTH 50
#define FORCA 80
#define CONN 2

//Server variables
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
struct sockaddr_in myself, client;
socklen_t client_size;
int socket_fd;
int connection_fd[CONN];
int jogador_vivo[CONN];

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int active_conn = CONN;

int main ()
{
  srand(time(NULL));
  ListComida *lc = new ListComida();
  ListPlayers *lp = new ListPlayers();
  lc->geraListaAleatoria(20,HEIGTH,WIDTH);
  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;


  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  myself.sin_family = AF_INET;
  myself.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(myself.sin_addr));
  if (bind(socket_fd, (struct sockaddr*)&myself, sizeof(myself)) != 0) {
    std::cout << " It was not possible to start the server \n ";
    return 0;
  }
  listen(socket_fd, 2);
  GameController *gc = new GameController(lc,lp);

  //connect the clients
  client_size = (socklen_t)sizeof(client);
  std::cout << " Waiting the connections. \n";
  for (int i = 0; i < CONN; i++) {
    int conn_fd;
    conn_fd = accept(socket_fd, (struct sockaddr*)&client, &client_size);
    connection_fd[i] = conn_fd;
    lp->addPlayer(WIDTH,HEIGTH);
    std::cout << " Someone connected \n " << CONN - i - 1 << " players remaining. \n";
    char char_auxiliar[64];
    std::snprintf(char_auxiliar, sizeof char_auxiliar, "%i", i);
    send(connection_fd[i], char_auxiliar, 1, 0);
    jogador_vivo[i] = 1;
  }

  Fisica *f = new Fisica(20,lp);
  while (1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;
    gc->verifica_e_realiza_captura();
    std::string data_to_send = gc->serialize();
    for(int l = 0; l<CONN; l++){
      int i = send(connection_fd[l], data_to_send.c_str(), data_to_send.length(), 0);
      char input_teclado[2];
      int msglen = recv(connection_fd[l], &input_teclado, 1, MSG_DONTWAIT);
      if(msglen>0) {
        char c = input_teclado[0];
        if (c=='w') {
          f->aplica_forca(deltaT, -FORCA, 0.0, l);
        } else if (c=='s'){
          f->aplica_forca(deltaT, FORCA, 0.0, l);
        } else if (c=='a'){
          f->aplica_forca(deltaT, 0.0, -FORCA, l);
        } else if (c=='d'){
          f->aplica_forca(deltaT, 0.0, FORCA, l);
        }
      }
    }
    f->update(deltaT);
  }
}
