#ifndef PLAYER_HPP
#define PLAYER_HPP
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


class Enemy {
	private:
		int x;
		int y;
	public:
		Enemy(int x, int y);
		void update(int x, int y);
		~Enemy();
		int get_x();
		int get_y();
};
#endif
