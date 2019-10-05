/*
	Paulo Roberto Andrade Filho - LAB3. RA156951
*/
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

#include "oo_model.hpp"

#include <ncurses.h>
using namespace std::chrono;

/*
	Construtor Player: Cria um Player novo
*/
Player::Player(float massa, float x, float y, float vx, float vy, float ax, float ay, float am) {
	this->massa = massa;
	this->posicao_x = x;
	this->posicao_y = y;
	this->velocidade_x = vx;
	this->velocidade_y = vy;
	this->aceleracao_x = ax;
	this->aceleracao_y = ay;
	this->amortecimento = am;
}

/*
	Getters Player
*/
// Get massa
float Player::get_massa() {
	return this->massa;
}

//	Get posicao x
float Player::get_x() {
	return this->posicao_x;
}

//	Get posicao y
float Player::get_y() {
	return this->posicao_y;
}

//	Get velocidade x
float Player::get_vx() {
	return this->velocidade_x;
}

//	Get velocidade y
float Player::get_vy() {
	return this->velocidade_y;
}

//	Get aceleracao_x
float Player::get_ax() {
	return this->aceleracao_x;
}

//	Get aceleracao_y
float Player::get_ay() {
	return this->aceleracao_y;
}

//	Get amortecimento
float Player::get_am() {
	return this->amortecimento;
}

/*
	Setters Player
*/
// update a massa do jogador
void Player::set_massa(float massa) {
	this->massa = massa;
}

// update as posicoes e as velocidades do jogador
void Player::update(float x, float y, float vx, float vy) {
	this->posicao_x = x;
	this->posicao_y = y;
	this->velocidade_x = vx;
	this->velocidade_y = vy;
}

// Update as posicoes, velocidades e aceleracoes
void Player::update(float x, float y, float vx, float vy, float ax, float ay) {
	this->posicao_x = x;
	this->posicao_y = y;
	this->velocidade_x = vx;
	this->velocidade_y = vy;
	this->aceleracao_x = ax;
	this->aceleracao_y = ay;
}

/*
	Construtor Fisica - cria uma nova fisica
*/
Fisica::Fisica(Player *jogador, float max_vel) {
	this->jogador = jogador;
	this->max_vel = max_vel;
}

//	Atualiza o modelo físico
void Fisica::update(float deltaT) {
	Player *jog = this->jogador;
	float new_vel_x = jog->get_vx() + (float)deltaT * jog->get_ax() / 1000;
	float new_vel_y = jog->get_vy() + (float)deltaT * jog->get_ay() / 1000;

	float new_pos_x = jog->get_x() + (float)deltaT * new_vel_x / 1000;
	float new_pos_y = jog->get_y() + (float)deltaT * new_vel_y / 1000;

	float new_aceleracao_x = (-jog->get_am() * new_vel_x) / jog->get_massa();
	float new_aceleracao_y = (-jog->get_am() * new_vel_y) / jog->get_massa();

	if (new_pos_x < 1) {
		if (new_pos_y < 1) {
			jog->update(1, 1, 0.0, 0.0, 0.0, 0.0);
		} else {
			jog->update(1, new_pos_y, 0.0, new_vel_y, 0.0, new_aceleracao_y);
		}
	}
	else {
		if (new_pos_y < 1) {
			jog->update(new_pos_x, 1, new_vel_x, 0.0, new_aceleracao_x, 0.0);
		} else {
			jog->update(new_pos_x, new_pos_y, new_vel_x, new_vel_y, new_aceleracao_x, new_aceleracao_y);
		}
	}
}

//	Aplica uma força ao corpo
void Fisica::aplica_forca(float deltaT, float forca_x, float forca_y) {
	Player *jog = this->jogador;
	float new_vel_x = jog->get_vx() + (float)deltaT * jog->get_ax() / 1000;
	float new_vel_y = jog->get_vy() + (float)deltaT * jog->get_ay() / 1000;

	float new_pos_x = jog->get_x() + (float)deltaT * new_vel_x / 1000;
	float new_pos_y = jog->get_y() + (float)deltaT * new_vel_y / 1000;

	float new_aceleracao_x = (forca_x - jog->get_am() * new_vel_x) / jog->get_massa();
	float new_aceleracao_y = (forca_y - jog->get_am() * new_vel_y) / jog->get_massa();

	if (new_pos_x < 1) {
		if (new_pos_y < 1) {
			jog->update(1, 1, 0.0, 0.0, 0.0, 0.0);
		} else {
			jog->update(1, new_pos_y, 0.0, new_vel_y, 0.0, new_aceleracao_y);
		}
	}
	else {
		if (new_pos_y < 1) {
			jog->update(new_pos_x, 1, new_vel_x, 0.0, new_aceleracao_x, 0.0);
		} else {
			jog->update(new_pos_x, new_pos_y, new_vel_x, new_vel_y, new_aceleracao_x, new_aceleracao_y);
		}
	}
}

/*
	Construtor Tela - cria uma nova tela
*/
Tela::Tela(Player *ldc, int largura, int comprimento, int tela_player, ListComida *lc) {
	this->jogador = ldc;
	this->largura = largura;
	this->tela_player = tela_player;
	this->comprimento = comprimento;
	this->listaComidas = lc;
}

void Tela::init() {
	int i;
	initscr();
	if (has_colors() == FALSE) { }
	else {
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(1));
	}

	i = (int)this->tela_player / 2 + 1;
	raw();
	curs_set(0);
	move(i, i);
	echochar('o');
}

ListComida* Tela::get_lc(){
	return this->listaComidas;
}

void Tela::update() {
	int x, y, meio, right_screen_bound;
	char *char_array;

	x = (int)(this->jogador->get_x());
	y = (int)(this->jogador->get_y());
	meio = (int)(this->tela_player) / 2 + 1;
	std::vector<Comida *> *lco = this->get_lc()->getComidas();

	for (int i = 0; i<(lco)->size(); i++){

		int xComida = (*lco)[i]->get_x();
		int yComida = (*lco)[i]->get_y();
		char xsa[64];
		char ysa[64];
		std::snprintf(xsa, sizeof xsa, "%i", xComida);
		std::snprintf(ysa, sizeof ysa, "%i", yComida);

		mvaddstr(9, 20, xsa);
		mvaddstr(8, 20, ysa);

	}

	int right_bound = y + meio;
	int left_bound = y - meio;
	int top_bound = x - meio;
	int bottom_bound = x + meio;

	if (top_bound <= 0) {
		mvaddstr(meio - x - 1, 0, "           ");
		mvaddstr(meio - x, 0, "===========");
		mvaddstr(meio - x + 1, 0, "           ");
	} else {
		mvaddstr(0, 0, "           ");
	}

	if (left_bound <= 0) {
		for (int i = 0; i < this->tela_player; i++) {
			move(i, meio -y);
			echochar('|');
		}
		for (int i = 0; i < this->tela_player; i++) {
			move(i, meio - y - 1);
			echochar(' ');
		}
		for (int i = 0; i < this->tela_player; i++) {
			move(i, meio - y + 1);
			echochar(' ');
		}
	} else {
		for (int i = 0; i < this->tela_player; i++) {
			move(i, 0);
			echochar(' ');
		}
	}

	char buffer[64];
	char buffer2[64];
	std::snprintf(buffer, sizeof buffer, "%i", (this->get_lc()->getComidas())->size());
	std::snprintf(buffer2, sizeof buffer, "%f", this->jogador->get_x());

	move(meio, meio);
	echochar('o');

	mvaddstr(10, 0, buffer);
	mvaddstr(11, 0, buffer2);
}

void Tela::stop() {
	endwin();
}

Tela::~Tela() {
	this->stop();
	;
}

void threadfun(char *keybuffer, int *control) {
	char c;
	while ((*control) == 1)
	{
		c = getch();
		if (c != ERR)
			(*keybuffer) = c;
		else
			(*keybuffer) = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

/*
	Construtor Teclado - cria um novo teclado
*/
Teclado::Teclado() {
}

Teclado::~Teclado() {
}

void Teclado::init() {
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	this->rodando = 1;
	std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
	(this->kb_thread).swap(newthread);
}

void Teclado::stop() {
	this->rodando = 0;
	(this->kb_thread).join();
}

char Teclado::getchar() {
	char c = this->ultima_captura;
	this->ultima_captura = 0;
	return c;
}
