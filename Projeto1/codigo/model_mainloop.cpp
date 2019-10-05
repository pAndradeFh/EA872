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

  Player *jog = new Player(20.0, WIDTH/2, HEIGTH/2, 0.0, 0.0, 0.0, 0.0);
  Fisica *f = new Fisica(jog);
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
  //   // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;
  //
  //   // Atualiza modelo
  //
  //   // Atualiza tela
  //
  //   // Lê o teclado
    char c = teclado->getchar();
    if (c=='w') {
      f->aplica_forca(deltaT,(float) 10.0, (float)  0.0);
    } else if ( c == 'q') {
      break;
    } else if (c=='s'){
      f->aplica_forca(deltaT,(float) 10.0, 0.0);
    } else if (c=='a'){
      f->aplica_forca(deltaT, (float) 0.0, (float) 10.0);
    } else if (c=='d'){
      f->aplica_forca(deltaT, (float) 0.0, (float) 10.0);
    };

    std::cout << jog->get_x() << jog->get_y() << '\n';

    tela->update();

    if ( (t1-T) > 10000 ) break;
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    i++;
  }
 tela->stop();
  teclado->stop();
  return 0;
}
