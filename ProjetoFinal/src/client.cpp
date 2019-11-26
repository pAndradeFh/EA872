/*
	Paulo Roberto Andrade Filho  RA156951 - PROJETO FINAL
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
// Bibliotecas e variaveis do servidor
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "json.hpp"
using json = nlohmann::json;
int socket_fd;


#include "audio.hpp"
#include "comida.hpp"
#include "player.hpp"
#include "gameController.hpp"
#include "fisica.hpp"
#include "tela.hpp"
#include "teclado_client.hpp"

#define WIDTH 100
#define HEIGTH 50

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int user_id;

int main ()
{
  int aux = 0;

  struct sockaddr_in target;
  std::cout << "Connecting to the server ...\n";
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(target.sin_addr));
  if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
    std::cerr << "It was not possible to connect to the server. \n Exiting. \n";
    exit(0);
  }
  char input_buffer[1000];
  int msg_len = recv(socket_fd, input_buffer, 1, 0);
  if(msg_len>0){
    std::cout << "Connected. \n";
    std::cout << "You're player number " << input_buffer<<".\n";
  }
 
  //criamos um novo teclado
  // Teclado_Client *teclado = new Teclado_Client();
  // teclado->init();

  std::cout << "Now waiting for other players. \n";
  int tamanho[1];
  while(aux == 0) {
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    char tamanho[1];
    int msg_len = recv(socket_fd, tamanho, 1, MSG_DONTWAIT);
    if(msg_len>0){
      std::cout << tamanho;
    }
  }

  // teclado->stop();
  // send(socket_fd, "&c", 1, 0);

  // Tela *tela = new Tela(jog, WIDTH, HEIGTH, SCREEN, lc, enemy);
  // tela->init();

  //Audio::Sample *mainTheme = new Audio::Sample();
  //Audio::Sample *victory = new Audio::Sample();
  //Audio::Sample *defeat  = new Audio::Sample();

  //mainTheme->load("assets/main_theme.dat");
  //victory->load("assets/victory.dat");
  //defeat->load("assets/defeat.dat");

  //Audio::Player *player = new Audio::Player();
  //player->init();
  //player->play(mainTheme);

  //
}
