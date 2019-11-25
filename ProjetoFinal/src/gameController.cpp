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

GameController::GameController(ListComida *lista_de_comidas){
  this->lista_de_comidas = lista_de_comidas;
  this->jogadores = new std::vector<Player *>(0);;
}

std::vector<Player*> *GameController::getJogadores(){
  return (this->jogadores);
}

void GameController::addRandomJogador(int height, int width){
  std::vector<Player*> *lp = this->getJogadores();
  int aux = 0;
  int xrand, yrand;
  while(aux == 0) {
    aux = 1;
    xrand = rand() % (height - 1) + 1;
    yrand = rand() % (width - 1) + 1;
    for (int k=0;k<(lp)->size();k++){
      if(xrand==(*lp)[k]->get_x() && yrand==(*lp)[k]->get_y()){
        aux = 0;
      }
    }
  }
  Player *jog = new Player(10, xrand, yrand, 0, 0, 0, 0, 0);
  lp->push_back(jog);
}

std::string GameController::serialize() {
  json j;
  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();
  std::vector<Player *> *lp = this->getJogadores();
  std::vector<int> comidas_y;
  std::vector<int> comidas_x;
  std::vector<int> players_y;
  std::vector<int> players_x;
  for(int i = 0; i < (lc)->size(); i ++){
    comidas_y.push_back((*lc)[i]->get_y());
    comidas_x.push_back((*lc)[i]->get_x());
  }
  for(int i = 0; i < (lp)->size(); i ++){
    players_x.push_back((*lp)[i]->get_x());
    players_y.push_back((*lp)[i]->get_y());
  }
  j["comidas_y"] = comidas_y;
  j["players_y"] = players_y;
  j["players_x"] = players_x;
  j["comidas_x"] = comidas_x;
  return j.dump();
}

//
//  O controlador de jogo efetua a captura da comida pelo jogador e veririca situação do jogo
//
int GameController::verifica_e_realiza_captura(){
  std::vector<Player*> *lp = this->getJogadores();

  for (int pla = 1;pla<(lp)->size(); pla++)
  {
    Player *jogador = (*lp)[pla];
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
  }
  return 3;
}
