/*
	Paulo Roberto Andrade Filho - Projeto 1 - RA1 56951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>

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

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;
    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};


#endif
