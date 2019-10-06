/*
	Paulo Roberto Andrade Filho - PROJETO1. RA156951
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

#define WIDTH 20
#define HEIGTH 30
#define SCREEN 11
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
void Player::update(float massa) {
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
	float massa = (float)(this->jogador->get_massa());
	meio = (int)(this->tela_player) / 2 + 1;
	std::vector<Comida *> *lco = this->listaComidas->getComidas();

	clear();
	for (int i = 0; i<lco->size(); i++) {
		int x_com = (int)((*lco)[i]->get_x());
		int y_com = (int)((*lco)[i]->get_y());
		if(x_com - x <= meio-1 && y_com - y <= meio-1 ){
			mvaddch(x_com - x + meio, y_com - y + meio,  '*');
		}
	}

	char xsa[64];
	std::snprintf(xsa, sizeof xsa, "%f", this->jogador->get_massa());
	mvaddstr(12, 0, xsa);
	//
	// char xsa1[64];
	// std::snprintf(xsa1, sizeof xsa1, "%i", (*lco)[1]->get_x());
	// mvaddstr(10, 20, xsa1);
	//
	// char xsa2[64];
	// std::snprintf(xsa2, sizeof xsa2, "%i", (*lco)[2]->get_x());
	// mvaddstr(11, 20, xsa2);

	int right_bound = y + meio;
	int left_bound = y - meio;
	int top_bound = x - meio;
	int bottom_bound = x + meio;

	if (top_bound <= 0) {
		mvaddstr(meio - x - 1, 0, "           ");
		mvaddstr(meio - x, 0, "===========");
		mvaddstr(meio - x + 1, 0, "           ");
	} else if(bottom_bound >= HEIGTH){
		mvaddstr(HEIGTH + meio - x - 1, 0, "           ");
		mvaddstr(HEIGTH + meio - x, 0, "===========");
		mvaddstr(HEIGTH + meio - x + 1, 0, "           ");
	} else  {
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
	} else if(right_bound >= WIDTH){
		for (int i = 0; i < this->tela_player; i++) {
			move(i, WIDTH + meio - y + 1);
			echochar('|');
		}
		for (int i = 0; i < this->tela_player; i++) {
			move(i, WIDTH + meio - y );
			echochar(' ');
		}
		for (int i = 0; i < this->tela_player; i++) {
			move(i, WIDTH + meio - y + 2);
			echochar(' ');
		}
	} else {
		for (int i = 0; i < this->tela_player; i++) {
			move(i, 0);
			echochar(' ');
		}
	}

		move(meio, meio);
		echochar('o');

	if(massa >= 20){
		move(meio - 1, meio);
		echochar('o');
	}

	if(massa >= 30){
		move(meio - 1, meio + 1);
		echochar('o');
	}

	if(massa >= 40){
		move(meio, meio + 1);
		echochar('o');
	}

	if(massa >= 50){
		move(meio - 1, meio + 1);
		echochar('o');
	}

	if(massa >= 60){
		move(meio+1, meio + 1);
		echochar('o');
	}

	if(massa >= 70){
		move(meio+1, meio);
		echochar('o');
	}

	if(massa >= 80){
		move(meio+1, meio - 1);
		echochar('o');
	}

	if(massa >= 90){
		move(meio, meio - 1);
		echochar('o');
	}

	if(massa >= 100){
		move(meio-1, meio - 1);
		echochar('o');
	}

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
