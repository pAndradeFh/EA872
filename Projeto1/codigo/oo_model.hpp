/*
	Paulo Roberto Andrade Filho - Projeto 1 - RA1 56951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>

/*
	Classe Player - implementa um usuario
*/
class Player {
	private:
	float massa;
	float posicao_x;
	float posicao_y;
	float velocidade_x;
	float velocidade_y;
	float aceleracao_x;
	float aceleracao_y;

	public:
	Player(float massa, float x, float y, float vx, float vy, float ax, float ay);
	void update(float x, float y, float vx, float vy);
	void update(float x, float y, float vx, float vy, float ax, float ay);
	void set_massa(float massa);
	float get_massa();
	float get_x();
	float get_y();
	float get_vx();
	float get_vy();
	float get_ax();
	float get_ay();
};

class Fisica {
  private:
    Player *jogador;

  public:
    Fisica(Player *jogador);
		void update(float deltaT);
		void aplica_forca(float deltaT, float forca_x, float forca_y);
};

class Tela {
  private:
    Player *jogador;
    int largura;
		int comprimento;
		int tela_player;

  public:
    Tela(Player *ldc, int largura, int comprimento, int tela_player);
    ~Tela();
    void stop();
    void init();
    void update();
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
