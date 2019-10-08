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
	float amortecimento;
	float posicao_x;
	float posicao_y;
	float velocidade_x;
	float velocidade_y;
	float aceleracao_x;
	float aceleracao_y;

	public:
	Player(float massa, float x, float y, float vx, float vy, float ax, float ay, float am);
	void update(float x, float y, float vx, float vy);
	void update(float x, float y, float vx, float vy, float ax, float ay);
	void update(float massa);
	float get_massa();
	float get_x();
	float get_y();
	float get_vx();
	float get_vy();
	float get_ax();
	float get_ay();
	float get_am();
};

class Fisica {
  private:
    Player *jogador;
		float max_vel;

  public:
    Fisica(Player *jogador, float max_vel);
		void update(float deltaT);
		void aplica_forca(float deltaT, float forca_x, float forca_y);
};

class Comida {
	private:
		int x;
		int y;
	public:
		Comida(int x, int y);
		~Comida();
		int get_x();
		int get_y();
};

class ListComida {
	private:
		std::vector<Comida*> *comidas;
	public:
		ListComida();
    void hard_copy(ListComida *ldc);
    void add_corpo(Comida *c);
		void geraListaAleatoria(int numero, int height, int width);
		std::vector<Comida *> *getComidas();
};

class Enemy {
	private:
		int x;
		int y;
	public:
		Enemy(int x, int y);
		~Enemy();
		int get_x();
		int get_y();
		void random_move();
};

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

class GameController {
	public:
		ListComida *lista_de_comidas;
		Player *jogador;
		Enemy *enemy;
		GameController(ListComida *lista_de_comidas, Player *ldc, Enemy *enemy);
		void verifica_e_realiza_captura();
};

#endif
