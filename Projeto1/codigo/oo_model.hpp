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
	void update_player(float x, float y, float vx, float vy);
	void update_player_aceleracao(float x, float y, float vx, float vy, float ax, float ay);
	void set_massa(float massa);
	float get_massa();
	float get_x();
	float get_y();
	float get_vx();
	float get_vy();
	float get_ax();
	float get_ay();
};

/*
class Corpo {
  private:
  float massa;
  float velocidade;
  float posicao;
  float aceleracao;
  float amortecimento;
  float constante_mola;

  public:
  Corpo(float massa, float velocidade, float posicao, float amortecimento, float constante_mola);
  void update(float nova_velocidade, float nova_posicao, float nova_aceleracao);
  float get_massa();
  float get_velocidade();
  float get_posicao();
  float get_aceleracao();
  float get_constante_mola();
  float get_amortecimento();
};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};
*/

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
    Player *jogador, *jogador_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(Jogador *ldc, int maxI, int maxJ, float maxX, float maxY);
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
