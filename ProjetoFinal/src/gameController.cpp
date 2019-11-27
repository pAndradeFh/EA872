#include <chrono>
#include "gameController.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <vector>
using namespace std::chrono;

#include <string>
#include <cstring>
#include "json.hpp"
using json = nlohmann::json;

#define WIDTH 50
#define HEIGTH 50
#define MEIO 11


GameController::GameController(ListComida *lista_de_comidas, ListPlayers *lista_de_jogadores){
  this->lista_de_comidas = lista_de_comidas;
  this->lista_de_jogadores = lista_de_jogadores;
}

std::vector<Player*> *GameController::getJogadores(){
  return (this->lista_de_jogadores)->getJogadores();
}

std::string GameController::serialize(int *ativos, int size, int tempo) {
  json j;
  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();
  std::vector<Player *> *lp = this->getJogadores();
  std::vector<int> comidas_y;
  std::vector<int> comidas_x;
  std::vector<int> players_y;
  std::vector<int> points;
  std::vector<int> vetor_ativos;
  std::vector<int> players_x;
  for(int i = 0; i < (lc)->size(); i ++){
    comidas_y.push_back((*lc)[i]->get_y());
    comidas_x.push_back((*lc)[i]->get_x());
  }
  for (int i = 0; i < size; i++){
    vetor_ativos.push_back(ativos[i]);
  }
  for(int i = 0; i < (lp)->size(); i ++){
    players_x.push_back((*lp)[i]->get_x());
    players_y.push_back((*lp)[i]->get_y());
    points.push_back((*lp)[i]->get_massa());
  }
  j["comidas_y"] = comidas_y;
  j["players_y"] = players_y;
  j["players_x"] = players_x;
  j["comidas_x"] = comidas_x;
  j["points"] = points;
  j["ativos"] = vetor_ativos;
  j["tempo"] = tempo;
  return j.dump();
}

//
//  O controlador de jogo efetua a captura da comida pelo jogador e veririca situação do jogo
//
int GameController::verifica_e_realiza_captura(){
  std::vector<Comida *> *lc = this->lista_de_comidas->getComidas();

  int xrand = rand() % 200 + 1;
  if (xrand <= 8){
    int aux = 0;
    int xrand, yrand;
    while(aux==0) {
      aux = 1;
      int xrand = rand() % (WIDTH - 1) + 1;
      int yrand = rand() % (HEIGTH - 1) + 1;
      for (int k=0;k<(lc)->size();k++){
        if(xrand==(*lc)[k]->get_x() && yrand==(*lc)[k]->get_y()){
          aux = 0;
        }
      }
    }
    Comida *c = new Comida(xrand, yrand);
    this->lista_de_comidas->add_corpo(c);
  }

  std::vector<Player*> *lp = this->getJogadores();

  for (int pla = 0;pla<(lp)->size(); pla++)
  {
    Player *jogador = (*lp)[pla];
    float massa = jogador->get_massa();

    int jx = (int)(jogador->get_x());
    int jy = (int)(jogador->get_y());

    for (int enemy = 0; enemy<(lp)->size(); enemy++){
      if(enemy!=pla){
          float massa_enemy = (*lp)[enemy]->get_massa();
          int e_x = (*lp)[enemy]->get_x();
          int e_y = (*lp)[enemy]->get_y();

      }
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
  return 1;
}
