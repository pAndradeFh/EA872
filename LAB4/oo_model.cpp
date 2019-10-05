/*
	Paulo Roberto Andrade Filho - LAB3. RA156951
*/
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "oo_model.hpp"

#include <ncurses.h>
using namespace std::chrono;

Corpo::Corpo(float massa, float velocidade, float posicao, float amortecimento, float constante_mola) {
  this->massa = massa;
  this->velocidade = velocidade;
  this->posicao = posicao;
  this->constante_mola = constante_mola;
  this->amortecimento = amortecimento;
  this->aceleracao = (-amortecimento*velocidade-constante_mola*posicao)/massa;
}

void Corpo::update(float nova_velocidade, float nova_posicao, float nova_aceleracao) {
  this->velocidade = nova_velocidade;
  this->posicao = nova_posicao;
  this->aceleracao = nova_aceleracao;
}

float Corpo::get_massa() {
  return this->massa;
}

float Corpo::get_velocidade() {
  return this->velocidade;
}

float Corpo::get_posicao() {
  return this->posicao;
}


float Corpo::get_aceleracao(){
  return this->aceleracao;
}

float Corpo::get_amortecimento(){
  return this->amortecimento;
}

float Corpo::get_constante_mola(){
  return this->constante_mola;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_massa(),\
                          (*corpos)[k]->get_posicao(),\
                          (*corpos)[k]->get_velocidade(),\
                          (*corpos)[k]->get_amortecimento(),\
	           	  (*corpos)[k]->get_constante_mola() );
    this->add_corpo(c);
  }

}

void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT, float F) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    float new_vel = (*c)[i]->get_velocidade() + (float)deltaT * (*c)[i]->get_aceleracao()/1000;
    float new_pos = (*c)[i]->get_posicao() + (float)deltaT * new_vel/1000;
    float new_acel = (F-(*c)[i]->get_amortecimento()*new_vel -(*c)[i]->get_constante_mola()*new_pos)/(*c)[i]->get_massa();
    (*c)[i]->update(new_vel, new_pos, new_acel);
  }
}

Tela::Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY) {
	this->lista = ldc;
	this->lista_anterior = new ListaDeCorpos();
	this->lista_anterior->hard_copy(this->lista);
	this->maxI = maxI;
	this->maxJ = maxJ;
	this->maxX = maxX;
	this->maxY = maxY;
}

void Tela::init() {
	 initscr();
  if(has_colors() == FALSE)
   {	

   } else {
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
   }

  raw();
  curs_set(0);
}

void Tela::update() {
	int i, meio; 
	std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();
	meio = (int) (this->maxI)/2;

	for (int k=0; k<corpos_old->size(); k++)
	{
		i = (int) ((*corpos_old)[k]->get_posicao()) * (this->maxI / this->maxX) +meio;
		if( i >=0 && i <= this->maxX){
		move(i, k);
		echochar(' ');
	}
}

std::vector<Corpo *> *corpos = this->lista->get_corpos();
for (int k=0; k<corpos->size(); k++)
{
    i = (int) ((*corpos)[k]->get_posicao()) * (this->maxI / this->maxX) + meio;

    if(i >=0 && i <= this->maxX){
	move(i, k); 
	echochar('o');
     }

    (*corpos_old)[k]->update(  (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao(),\
			       (*corpos)[k]->get_aceleracao());
  }
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}

void threadfun (char *keybuffer, int *control)
{
  char c;
  while ((*control) == 1) {
	c = getch();
	if (c!=ERR) (*keybuffer) = c;
	else (*keybuffer) = 0;
   	std::this_thread::sleep_for (std::chrono::milliseconds(10));
  }
  return;
}

Teclado::Teclado() {
}

Teclado::~Teclado() {
}

void Teclado::init() {
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);           

  this->rodando = 1;
  std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
  (this->kb_thread).swap(newthread);
}

void Teclado::stop() {
  this->rodando = 0;
  (this->kb_thread).join();
}

char Teclado::getchar() {
  char c = this->ultima_captura;
  this->ultima_captura = 0;
  return c;
}
