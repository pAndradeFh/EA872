/*
	Paulo Roberto Andrade Filho - PROJETO1. RA156951
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
#include "io.hpp"
#include "fisica.hpp"

#define WIDTH 20
#define HEIGTH 30
#define SCREEN 11
#define FORCA 65

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  srand(time(NULL));

  Audio::Sample *mainTheme = new Audio::Sample();
  Audio::Sample *victory = new Audio::Sample();
  Audio::Sample *defeat  = new Audio::Sample();

  mainTheme->load("assets/main_theme.dat");
  victory->load("assets/victory.dat");
  defeat->load("assets/defeat.dat");

  Audio::Player *player = new Audio::Player();
  player->init();
  player->play(mainTheme);

  //Gera um jogador em uma posição especifica
  Player *jog = new Player(10.0, 15, 10, 0.0, 0.0, 0.0, 0.0, 1);
  //Cria uma física nova
  Fisica *f = new Fisica(jog, 20);
  //Cria uma lista de objetos para serem comidas
  ListComida *lc = new ListComida();
  //Cria um inimigo
  Enemy *enemy = new Enemy((int)(jog->get_x() - 3),(int)(jog->get_y() - 3));
  //Cria um controlador de jogo
  GameController *gc = new GameController(lc, jog, enemy);
  //popula a lista em posicoes diferentes
  lc->geraListaAleatoria(20,HEIGTH,WIDTH);
  //Cria uma nova tela e a inicializa
  Tela *tela = new Tela(jog, WIDTH, HEIGTH, SCREEN, lc, enemy);
  tela->init();
  //Cria um novo teclado e o inicializa
  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;
  //
  int i = 0;
  //
  int aux = 0;
  //gera um menu
  tela->menu();
  //escolhe a opção de jogo
  while(aux == 0) {
      std::this_thread::sleep_for (std::chrono::milliseconds(50));
      char c = teclado->getchar();
      if(c == 't'){
        aux = 1;
      } else if (c == 'e'){
        aux = 2;
      } else if (c=='q'){
        aux = 3;
      }
  }

  T = get_now_ms();
  t1 = T;

  if(aux == 1){
      tela->msg();
      std::this_thread::sleep_for (std::chrono::milliseconds(4000));
      int ganhou = 3;
      while (ganhou == 3) {
        t0 = t1;
        t1 = get_now_ms();
        deltaT = t1-t0;
        //verifica se houve captura de comida
        ganhou = gc->verifica_e_realiza_captura();
        //lê os comandos do teclado e efetua a movimentação
        char c = teclado->getchar();
        if (c=='w') {
          f->aplica_forca(deltaT, -FORCA, 0.0);
        } else if ( c == 'q') {
          ganhou = 0;
          break;
        } else if (c=='s'){
          f->aplica_forca(deltaT, FORCA, 0.0);
        } else if (c=='a'){
          f->aplica_forca(deltaT, 0.0, -FORCA);
        } else if (c=='d'){
          f->aplica_forca(deltaT, 0.0, FORCA);
        } else {
          f->update(deltaT);
        }
        tela->update((int)(t1-T));
        if ( (t1-T) > 30000 ) {
          ganhou = 0;
        };
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
        i++;
      }
    if(ganhou == 0){
        player->pause();
        player->play(defeat);
    } else {
      player->pause();
      player->play(victory);
    }
    // mostra mensagem de derrota ou vitória
    tela->vitoria_ou_derrota(ganhou);
    std::this_thread::sleep_for (std::chrono::milliseconds(2000));
    //FIM
    tela->stop();
    teclado->stop();
    player->stop();
    return 0;
  } else {
    //Sai do programa
    tela->stop();
    teclado->stop();
    player->stop();
    return 0;
  }

}
