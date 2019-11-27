#include <chrono>

#include "fisica.hpp"
#include "player.hpp"
#include <ncurses.h>
#include <vector>
using namespace std::chrono;

#define WIDTH 30
#define HEIGTH 30
#define FORCA 80
#define CONN 4
/*
	Construtor Fisica - cria uma nova fisica
*/
Fisica::Fisica(float max_vel, ListPlayers *jogadores) {
	this->max_vel = max_vel;
	this->lista_de_jogadores = jogadores;
}

//	Atualiza o modelo físico
void Fisica::update(float deltaT) {
	std::vector<Player*> *jogadores = (this->lista_de_jogadores)->getJogadores();
	float max_vel = this->max_vel;
	for(int jk=0;jk<jogadores->size();jk++)
	{
		Player *jog = (*jogadores)[jk];
		float new_vel_x = jog->get_vx() + (float)deltaT * jog->get_ax() / 1000;
		if(new_vel_x > max_vel) new_vel_x = max_vel;
		float new_vel_y = jog->get_vy() + (float)deltaT * jog->get_ay() / 1000;
		if(new_vel_y > max_vel) new_vel_y = max_vel;
		float new_pos_x = jog->get_x() + (float)deltaT * new_vel_x / 1000;
		float new_pos_y = jog->get_y() + (float)deltaT * new_vel_y / 1000;

		float new_aceleracao_x = (-jog->get_am() * new_vel_x) / jog->get_massa();
		float new_aceleracao_y = (-jog->get_am() * new_vel_y) / jog->get_massa();

		if (new_pos_x < 1) {
			if (new_pos_y < 1) {
				jog->update(1, 1, 0.0, 0.0, 0.0, 0.0);
			} else if(new_pos_y > WIDTH + 1){
				jog->update(1, WIDTH, 0.0, 0.0, 0.0, 0.0);
			} else {
				jog->update(1, new_pos_y, 0.0, new_vel_y, 0.0, 0);
			}
		}
		else if(new_pos_x > HEIGTH){
			if (new_pos_y < 1) {
				jog->update(HEIGTH - 1, 1, 0.0, 0.0, 0.0, 0.0);
			} else if(new_pos_y > WIDTH + 1){
				jog->update(HEIGTH - 1, WIDTH, 0.0, 0.0, 0.0, 0.0);
			} else {
				jog->update(HEIGTH - 1, new_pos_y, 0.0, new_vel_y, 0.0, 0);
			}
		} else {
			if (new_pos_y < 1) {
				jog->update(new_pos_x, 1, new_vel_x, 0.0, new_aceleracao_x, 0.0);
			}  else if(new_pos_y > WIDTH + 1){
				jog->update(new_pos_x, WIDTH, new_vel_x, 0.0, 0.0, 0.0);
			} else {
				jog->update(new_pos_x, new_pos_y, new_vel_x, new_vel_y, new_aceleracao_x, new_aceleracao_y);
			}
		}
	}
}

//	Aplica uma força ao corpo
void Fisica::aplica_forca(float deltaT, float forca_x, float forca_y, int pos) {
	std::vector<Player*> *jogadores = (this->lista_de_jogadores)->getJogadores();
	Player *jog = (*jogadores)[pos];
	float new_vel_x = jog->get_vx() + (float)deltaT * jog->get_ax() / 1000;
	float new_vel_y = jog->get_vy() + (float)deltaT * jog->get_ay() / 1000;

	float new_pos_x = jog->get_x() + (float)deltaT * new_vel_x / 1000;
	float new_pos_y = jog->get_y() + (float)deltaT * new_vel_y / 1000;

	float new_aceleracao_x = (forca_x - jog->get_am() * new_vel_x) / jog->get_massa();
	float new_aceleracao_y = (forca_y - jog->get_am() * new_vel_y) / jog->get_massa();

	if (new_pos_x < 1) {
		if (new_pos_y < 1) {
			jog->update(1, 1, 0.0, 0.0, 0.0, 0.0);
		} else if(new_pos_y > WIDTH + 1){
			jog->update(1, WIDTH, 0.0, 0.0, 0.0, 0.0);
		} else {
			jog->update(1, new_pos_y, 0.0, new_vel_y, 0.0, 0);
		}
	}
	else if(new_pos_x > HEIGTH){
		if (new_pos_y < 1) {
			jog->update(HEIGTH - 1, 1, 0.0, 0.0, 0.0, 0.0);
		} else if(new_pos_y > WIDTH + 1){
			jog->update(HEIGTH - 1, WIDTH, 0.0, 0.0, 0.0, 0.0);
		} else {
			jog->update(HEIGTH - 1, new_pos_y, 0.0, new_vel_y, 0.0, 0);
		}
	} else {
		if (new_pos_y < 1) {
			jog->update(new_pos_x, 1, new_vel_x, 0.0, new_aceleracao_x, 0.0);
		}  else if(new_pos_y > WIDTH + 1){
			jog->update(new_pos_x, WIDTH, new_vel_x, 0.0, 0.0, 0.0);
		} else {
			jog->update(new_pos_x, new_pos_y, new_vel_x, new_vel_y, new_aceleracao_x, new_aceleracao_y);
		}
	}
}
