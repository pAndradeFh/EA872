#include <chrono>
#include "gameController.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <vector>
using namespace std::chrono;

#include <string>
#include <cstring>
// JSON library
#include "json.hpp"
using json = nlohmann::json;

GameController::GameController(ListComida *lista_de_comidas, Player *jog){
  this->jogador = jog;
  this->lista_de_comidas = lista_de_comidas;
}


std::string GameController::serialize() {
  json j;
  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();
  std::vector<int> comidas_y;
  std::vector<int> comidas_x;
  for(int i = 0; i < (lc)->size(); i ++){
    comidas_y.push_back((*lc)[i]->get_y());
    comidas_x.push_back((*lc)[i]->get_y());
  }
  j["comidas_y"] = comidas_y;
  j["comidas_x"] = comidas_x;
  return j.dump();
}

//
//  O controlador de jogo efetua a captura da comida pelo jogador e veririca situação do jogo
//
int GameController::verifica_e_realiza_captura(){
  Player *jogador = this->jogador;
  float massa = jogador->get_massa();

  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();


  int jx = (int)(jogador->get_x());
  int jy = (int)(jogador->get_y());

  if(massa>=100){
    return 1;
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
