/*
	Paulo Roberto Andrade Filho - LAB3. RA156951
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{

  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, 20, 20, 20, 20);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();


  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  int i = 0;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo

    // Atualiza tela

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='w') {
      f->update(deltaT,500);
    } else
    if (c=='q') {
      break;
    } else if (c=='s'){
      f->update(deltaT,-500);
	} else
	{
       f->update(deltaT,0);
    }

	tela->update();

    // Condicao de parada
    if ( (t1-T) > 20000 ) break;
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}
