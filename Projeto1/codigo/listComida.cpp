/*
	Paulo Roberto Andrade Filho - LAB3. RA156951
*/
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>

#include "oo_model.hpp"

#include <ncurses.h>
using namespace std::chrono;

ListComida::ListComida(){
  this->comidas = new std::vector<Comida *>(0);
}

std::vector<Comida *> *ListComida::getComidas(){
  return this->comidas;
}

void ListComida::add_corpo(Comida *c){
  (this->getComidas())->push_back(c);
}


void ListComida::geraListaAleatoria(int numero, int height, int width){
  int xrand, yrand;
  std::vector<Comida *> *coms = this->getComidas();
  for (int i=1; i<= numero; i++){
    xrand = rand() % (height-1) + 1;
    yrand = rand() % (width-1) + 2;
    if((coms)->size() == 0){
      Comida *c = new Comida(xrand,yrand);
      this->add_corpo(c);
    } else {

    }
  }
}

Comida::Comida(int x, int y){
  this->x = x;
  this->y = y;
}

int Comida::get_x(){
  return this->x;
}

int Comida::get_y(){
  return this->y;
}
