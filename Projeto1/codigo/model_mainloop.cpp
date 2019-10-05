/*
	Paulo Roberto Andrade Filho - Projeto 1. RA156951
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "oo_model.hpp"

#define WIDTH 100
#define HEIGTH 50
#define SCREEN 11

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{

  //Player *jog = new Player(10.0, HEIGTH/2, WIDTH/2, 0.0, 0.0, 0.0, 0.0, 1);
  Player *jog = new Player(10.0, 6, 6, 0.0, 0.0, 0.0, 0.0, 1);
  Fisica *f = new Fisica(jog, 20);
  //
  Tela *tela = new Tela(jog, WIDTH, HEIGTH, SCREEN);
  tela->init();
  //
  Teclado *teclado = new Teclado();
  teclado->init();
  //
  //
  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;
  //
  int i = 0;
  //
  T = get_now_ms();
  t1 = T;
  while (1) {
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    char c = teclado->getchar();
    if (c=='w') {
      f->aplica_forca(deltaT, -10.0, 0.0);
    } else if ( c == 'q') {
      break;
    } else if (c=='s'){
      f->aplica_forca(deltaT, 10.0, 0.0);
    } else if (c=='a'){
      f->aplica_forca(deltaT, 0.0, -10.0);
    } else if (c=='d'){
      f->aplica_forca(deltaT, 0.0, 10.0);
    } else {
      f->update(deltaT);
    }

    tela->update();

    if ( (t1-T) > 40000 ) break;
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}
