#include <chrono>
#include "gameController.hpp"
#include "player.hpp"
#include <ncurses.h>
using namespace std::chrono;


GameController::GameController(ListComida *lista_de_comidas, Player *jog, Enemy * enemy){
  this->jogador = jog;
  this->lista_de_comidas = lista_de_comidas;
  this->enemy = enemy;
}

Enemy *GameController::get_enemy() {
  return this->enemy;
}

//
//  O controlador de jogo efetua a captura da comida pelo jogador e veririca situação do jogo
//
int GameController::verifica_e_realiza_captura(){
  Player *jogador = this->jogador;
  float massa = jogador->get_massa();

  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();

  Enemy *inimigo = this->get_enemy();

  //verifica se o inimigo está sobre o player
  int e_x = (int)(inimigo->get_x());
  int e_y = (int)(inimigo->get_y());
  int jx = (int)(jogador->get_x());
  int jy = (int)(jogador->get_y());

  if(massa >= 10 && e_x == jx && e_y == jy){
    return 0;
  }

  if(massa >= 20 && e_x == jx - 1 && e_y == jy){
    return 0;
  }
  if(massa >= 30 && e_x == jx - 1 && e_y == jy + 1){
    return 0;
  }
  if(massa >= 40 && e_x == jx && e_y == jy + 1){
    return 0;
  }
  if(massa >= 50 && e_x == jx + 1 && e_y == jy + 1){
    return 0;
  }
  if(massa >= 60 && e_x == jx + 1 && e_y == jy){
    return 0;
  }
  if(massa >= 70 && e_x == jx + 1 && e_y == jy - 1){
    return 0;
  }
  if(massa >= 80 && e_x == jx && e_y == jy - 1){
    return 0;
  }
  if(massa >= 90 && e_x == jx - 1 && e_y == jy - 1){
    return 0;
  }

  if(massa>=100){
    return 1;
  }

  //  Realiza movimentos aleatorios do inimigo na direção do player
  int xrand = rand() % 1000 + 1;
  if (xrand <= 8){
    int new_x, new_y;
    if(e_x < jogador->get_x()){
      new_x = e_x + 1;
    } else if(e_x > jogador->get_x()){
      new_x = e_x - 1;
    } else {
      new_x = e_x;
    }
    if(e_y < jogador->get_y()){
      new_y = e_y + 1;
    } else if(e_y > jogador->get_y()){
      new_y = e_y - 1;
    } else {
      new_y = e_y;
    }
    inimigo->update(new_x,new_y);
  }

  //  veririfica se o jogador comeu alguma comida
  for(int i = 0; i < (lc)->size(); i ++){
    if((int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())) {
      (lc)->erase((lc)->begin() + i);
      jogador->update(jogador->get_massa() + 10);
    }

    if(massa >= 20 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x() - 1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())) {
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa() + 10);
    }

    if(massa >= 30 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x() - 1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y() + 1)){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=40 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y()+ 1 )){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=50 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x() + 1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y() + 1)){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=60 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x() + 1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y())){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=70 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x() + 1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y() - 1)){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=80 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x()) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y()-1)){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }

    if(massa>=90 && (int)((*lc)[i]->get_x()) == (int)(jogador->get_x()-1) && (int)((*lc)[i]->get_y()) == (int)(jogador->get_y()-1)){
      (lc)->erase((lc)->begin()+i);
      jogador->update(jogador->get_massa()+10);
    }
  }
  return 3;
}
