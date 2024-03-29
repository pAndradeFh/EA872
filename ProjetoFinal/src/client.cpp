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

#define WIDTH 50
#define HEIGTH 50
#define MEIO 11

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
  char input_buffer[1];
  int msg_len = recv(socket_fd, input_buffer, 1, 0);
  if(msg_len>0){
    std::cout << "Connected. \n";
    std::cout << "You're player number " << input_buffer <<".\n";
  }
  int n_client;
  sscanf(input_buffer,"%i", &n_client);

  //criamos um novo teclado
  Teclado_Client *teclado = new Teclado_Client();
  teclado->init();

  Tela *tela = new Tela(HEIGTH,WIDTH, n_client, MEIO);
  tela->init();

  std::cout << "Now waiting for other players to start. \n";
  int tamanho[1];

  // tela->menu();
  // std::this_thread::sleep_for (std::chrono::milliseconds(1000));

  //Audio::Sample *mainTheme = new Audio::Sample();
  //Audio::Sample *victory = new Audio::Sample();
  //Audio::Sample *defeat  = new Audio::Sample();

  //mainTheme->load("assets/main_theme.dat");
  //victory->load("assets/victory.dat");
  //defeat->load("assets/defeat.dat");

  //Audio::Player *player = new Audio::Player();
  //player->init();
  //player->play(mainTheme);

  while(1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    const unsigned int MAX_BUF_LENGTH = 4096;
    std::vector<char> buffer(MAX_BUF_LENGTH);
    std::string rcv;
    int bytesReceived = 0;
    do {
      bytesReceived = recv(socket_fd, &buffer[0], buffer.size(), 0);
      if ( bytesReceived == -1 ) {
      } else {
         rcv.append( buffer.cbegin(), buffer.cend() );
      }
    } while ( bytesReceived == MAX_BUF_LENGTH );
    tela->update(rcv);
    if( (tela->ativos)[n_client]==2 ){
      std::cout<<"You win" << "\n";
      break;
    } else if ((tela->ativos)[n_client]==3){
      std::cout<<"You lose" << "\n";
      break;
    }
    tela->update();
    char c = teclado->getchar();
    char envio[1];
    int flag = 0;
    if (c=='w') {
        flag = 1;
        envio[0] = 'w';
    } else if ( c == 'q') {
        break;
    } else if (c=='s'){
        flag = 1;
        envio[0] = 's';
    } else if (c=='a'){
        flag = 1;
        envio[0] = 'a';
    } else if (c=='d'){
        flag = 1;
        envio[0] = 'd';
    }
    if(flag == 1){
      send(socket_fd, envio, 1, 0);
    }
  }

  teclado->stop();
  tela->stop();
  //player->stop();
}
