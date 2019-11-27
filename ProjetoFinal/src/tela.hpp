/*
	Paulo Roberto Andrade Filho - Laboratório 6 - RA 156951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <ncurses.h>
#include "json.hpp"
using json = nlohmann::json;

class Tela {
  private:
    ListPlayers *jogadores;
    int largura;
		int comprimento;
		int tela_player;
    int meio;
    int tempo;
		ListComida *listaComidas;
    std::vector<int> ativos;
  public:
    Tela(int largura, int comprimento, int tela_player, int meio);
    void update(std::string info);
    ~Tela();
		ListComida* get_lc();
    void stop();
    void init();
    void update();
		void menu();
		void msg();
		void vitoria_ou_derrota(int vit_der);
};


#endif
