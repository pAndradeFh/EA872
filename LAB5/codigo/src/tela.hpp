/*
	Paulo Roberto Andrade Filho - Laboratório 6 - RA 156951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <ncurses.h>

class Tela {
  private:
    Player *jogador;
		Enemy *enemy;
    int largura;
		int comprimento;
		int tela_player;
		ListComida *listaComidas;

  public:
    Tela(Player *ldc, int largura, int comprimento, int tela_player, ListComida *lc, Enemy *enemy);
    ~Tela();
		ListComida* get_lc();
		Enemy* get_enemy();
    void stop();
    void init();
    void update(int tempo);
		void menu();
		void msg();
		void vitoria_ou_derrota(int vit_der);
};


#endif
