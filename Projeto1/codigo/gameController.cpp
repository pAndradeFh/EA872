#include <vector>
#include <chrono>
#include <thread>
#include <time.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "oo_model.hpp"
#include <ncurses.h>
using namespace std::chrono;

GameController::GameController(ListComida *lista_de_comidas, Player *jog){
  this->jogador = jog;
  this->lista_de_comidas = lista_de_comidas;
}

void GameController::verifica_e_realiza_captura(){
  Player *jogador = this->jogador;
  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();
  float massa = jogador->get_massa();
  for(int i = 0; i < (lc)->size(); i ++){
    if((int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=20 && (int)((*lc)[i]->get_x()-1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=30 && (int)((*lc)[i]->get_x()-1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()+1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=40 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()+1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=50 && (int)((*lc)[i]->get_x()-1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()+1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=60 && (int)((*lc)[i]->get_x()+1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()+1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=70 && (int)((*lc)[i]->get_x()+1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=80 && (int)((*lc)[i]->get_x()+1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()-1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=90 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()-1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=100 && (int)((*lc)[i]->get_x()-1) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()-1) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }
  }
}
