/*
	Paulo Roberto Andrade Filho - Laboratório 6 - RA 156951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <ncurses.h>

class Tela {
  private:
    Player *jogador;
    int largura;
		int comprimento;
		int tela_player;
		ListComida *listaComidas;

  public:
    Tela(Player *ldc, int largura, int comprimento, int tela_player, ListComida *lc);
    ~Tela();
		ListComida* get_lc();
    void stop();
    void init();
    void update(int tempo);
		void menu();
		void msg();
		void vitoria_ou_derrota(int vit_der);
};


#endif
