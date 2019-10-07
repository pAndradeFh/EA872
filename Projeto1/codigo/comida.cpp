/*
	Paulo Roberto Andrade Filho - PROJETO 1. RA156951
*/
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "modelos.hpp"
#include <ncurses.h>
using namespace std::chrono;

Comida::Comida(int x, int y) {
  this->x = x;
  this->y = y;
}

int Comida::get_x(){
  return this->x;
}

int Comida::get_y(){
  return this->y;
}

ListComida::ListComida(){
  this->comidas = new std::vector<Comida *>(0);
}

std::vector<Comida *> *ListComida::getComidas(){
  return (this->comidas);
}

void ListComida::add_corpo(Comida *c){
  (this->getComidas())->push_back(c);
}

void ListComida::geraListaAleatoria(int numero, int height, int width){
  std::vector<Comida *> *coms = this->getComidas();
  for (int i=1; i<= numero; i++){
      if((coms)->size()==0) {
        int xrand = rand() % (height - 1) + 1;
        int yrand = rand() % (width - 1) + 1;
        Comida *c = new Comida(xrand, yrand);
        this->add_corpo(c);
      } else {
        int aux = 0;
        int xrand, yrand;
        while(aux==0) {
          aux = 1;
          xrand = rand() % (height - 1) + 1;
          yrand = rand() % (width - 1) + 1;
          for (int k=0;k<(coms)->size();k++){
            if(xrand==(*coms)[k]->get_x() && yrand==(*coms)[k]->get_y()){
              aux = 0;
            }
          }
        }
        Comida *c = new Comida(xrand, yrand);
        this->add_corpo(c);
      }
  }
}
