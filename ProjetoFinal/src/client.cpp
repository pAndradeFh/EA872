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
int socket_fd;

#include "audio.hpp"
#include "comida.hpp"
#include "player.hpp"
#include "gameController.hpp"
#include "fisica.hpp"
#include "tela.hpp"
#include "teclado_client.hpp"

#define WIDTH 20
#define HEIGTH 30
#define SCREEN 11
#define FORCA 110
#define CONN 4

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  srand(time(NULL));
  struct sockaddr_in target;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  Teclado_Client *teclado = new Teclado_Client();
  teclado->init();

  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(target.sin_addr));
  if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
    teclado->stop();
    return 0;
  }
  send(socket_fd, "&c", 1, 0);

  Tela *tela = new Tela(jog, WIDTH, HEIGTH, SCREEN, lc, enemy);
  tela->init();

  //Audio::Sample *mainTheme = new Audio::Sample();
  //Audio::Sample *victory = new Audio::Sample();
  //Audio::Sample *defeat  = new Audio::Sample();

  //mainTheme->load("assets/main_theme.dat");
  //victory->load("assets/victory.dat");
  //defeat->load("assets/defeat.dat");

  //Audio::Player *player = new Audio::Player();
  //player->init();
  //player->play(mainTheme);

  teclado->stop();

  //Gera um jogador em uma posição especifica
}
