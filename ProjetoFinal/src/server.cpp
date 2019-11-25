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

#define WIDTH 100
#define HEIGTH 50
#define FORCA 110
#define CONN 4

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int active_conn = 2;

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
  lp->addPlayer(WIDTH,HEIGTH);
  lp->addPlayer(WIDTH,HEIGTH);
  GameController *gc = new GameController(lc,lp);
  Fisica *f = new Fisica(20,lp);
  while (1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(2000));
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;
    std::string t = gc->serialize();
    std::cout << t << '\n';
    std::vector<Player*> *lp = gc->getJogadores();
    for(int l = 1; l<=(lp)->size(); l++){
      if (c=='w') {
          f->aplica_forca(deltaT, -FORCA, 0.0);
      } else if ( c == 'q') {
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
    }
  }
}
