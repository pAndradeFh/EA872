/*
	Paulo Roberto Andrade Filho - LAB4. RA156951
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

	Corpo *c1 = new Corpo(10, 5, 0, 1.5, 100);
	Corpo *c2 = new Corpo(5, 4, 0, 1.5, 100);
	Corpo *c3 = new Corpo(7, 0, 0, 1.5, 100);
	Corpo *c4 = new Corpo(10, 0, 0, 1.5, 100);
	Corpo *c5 = new Corpo(1, -4, 0, 1.5, 100);
	Corpo *c6 = new Corpo(10, -5, 0, 1.5, 100);

  	ListaDeCorpos *l = new ListaDeCorpos();
	l->add_corpo(c1);
	l->add_corpo(c2);
	l->add_corpo(c3);
	l->add_corpo(c4);
	l->add_corpo(c5);
	l->add_corpo(c6);

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

  	Audio::Sample *asample;
  	asample = new Audio::Sample();
  	asample->load("blip.dat");

  	Audio::Player *player;
  	player = new Audio::Player();

  	T = get_now_ms();
  	t1 = T;
  	while (1) {
		t0 = t1;
    		t1 = get_now_ms();
    		deltaT = t1-t0;    

    		char c = teclado->getchar();
    		if (c=='w') {
      			f->adicionaForca(deltaT,500);
			player->init();
			player->play(asample);
    		} else if (c=='q') {
      			break;
    		} else if (c=='s') {
      			f->adicionaForca(deltaT,-500);
			player->init();
			player->play(asample);
    		} else {
       			f->update(deltaT);
    		}

		tela->update();

    		if ( (t1-T) > 20000 ) break;

    		std::this_thread::sleep_for (std::chrono::milliseconds(100));
    		i++;

		player->stop();
		asample->set_position(0);
  	}
	
	tela->stop();
	teclado->stop();
	return 0;
}
