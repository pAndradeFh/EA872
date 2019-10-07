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
    void update();
		int menu();
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
		GameController(ListComida *lista_de_comidas, Player *ldc);
		ListComida *lista_de_comidas;
		Player *jogador;
		void verifica_e_realiza_captura();
};

#endif
