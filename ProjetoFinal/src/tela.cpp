#include <chrono>
#include <ncurses.h>
#include <stdio.h>
#include "player.hpp"
#include "comida.hpp"
#include "tela.hpp"
#include "json.hpp"

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
using json = nlohmann::json;

using namespace std::chrono;

#define WIDTH 100
#define HEIGTH 50
#define MEIO 11

/*
	Construtor Tela - cria uma nova tela
*/
Tela::Tela(int largura, int comprimento, int tela_player, int meio) {
	this->comprimento = comprimento;
	this->largura = largura;
	this->tela_player = tela_player;
	this->meio = meio;
}

void Tela::update(std::string info){
	json j;
	ListComida *lc = new ListComida();
	ListPlayers *lp = new ListPlayers();
  j = json::parse(info);
	std::vector<int> comidas_y;
	std::vector<int> comidas_x;
	std::vector<int> players_x;
	std::vector<int> players_y;
	std::vector<int> massa;
	for (auto& elem : j["comidas_y"]) {
			int elemento = (int) elem;
			comidas_y.push_back(elemento);
	}
	for (auto& elem : j["comidas_x"]) {
			int elemento = (int) elem;
			comidas_x.push_back(elemento);
	}
	for (auto& elem : j["players_x"]) {
			int elemento = (int) elem;
			players_x.push_back(elemento);
	}
	for (auto& elem : j["players_y"]) {
			int elemento = (int) elem;
			players_y.push_back(elemento);
	}

	for (auto& elem : j["points"]) {
			int elemento = (int) elem;
			massa.push_back(elemento);
	}

	for(int i=0;i<comidas_x.size();i++){
		Comida *aux = new Comida(comidas_x[i],comidas_y[i]);
		lc->add_corpo(aux);
	}

	for(int i=0;i<players_y.size();i++){
		Player *aux = new Player(massa[i],players_x[i],players_y[i]);
		lp->addPlayer(aux);
	}

	this->listaComidas = lc;
	this->jogadores = lp;
}

//inicia a tela
void Tela::init() {
	int i;
	initscr();
	raw();
	curs_set(0);
	if (has_colors() == FALSE) { }
	else {
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		attron(COLOR_PAIR(1));
	}
	erase();
	refresh();
}

ListComida* Tela::get_lc(){
	return this->listaComidas;
}

//
//	Classe Tela - view que apenas mostra as informações
//
void Tela::update() {
	int x, y, meio, right_screen_bound, x_e, y_e, massa;
	char *char_array;
	int posi = (int) this->tela_player;
	std::vector<Player*> *lc = this->jogadores->getJogadores();
	x = (int)((*lc)[posi]->get_x());
	massa = (int)((*lc)[posi]->get_massa());
	y = (int)((*lc)[posi]->get_y());
	meio = (int)(this->meio) / 2 + 1;
	std::vector<Comida *> *lco = this->listaComidas->getComidas();
	clear();

	for (int i = 0; i<lco->size(); i++) {
		int x_com = (int)((*lco)[i]->get_x());
		int y_com = (int)((*lco)[i]->get_y());
		if(x_com - x <= meio-1 && y_com - y <= meio-1 ){
			mvaddch(x_com - x + meio, y_com - y + meio,  '*');
		}
	}

	char xsa[64], xsa2[64];
	// std::snprintf(xsa, sizeof xsa, "%f", this->jogador->get_massa());
	// mvaddstr(12, 0, xsa);
	std::snprintf(xsa2, sizeof xsa2, "%i", x);
	mvaddstr(13, 0, xsa2);

	int right_bound = y + meio;
	int left_bound = y - meio;
	int top_bound = x - meio;
	int bottom_bound = x + meio;

	if (top_bound <= 0) {
		mvaddstr(meio - x, 0, "===========");
	}

	if(bottom_bound >= HEIGTH){
		mvaddstr(HEIGTH + meio - x, 0, "===========");
	}

	if (left_bound <= 0) {
		for (int i = 0; i < this->tela_player; i++) {
			move(i, meio -y);
			echochar('|');
		}
	}

	if(right_bound >= WIDTH){
		for (int i = 0; i < this->tela_player; i++) {
			move(i, WIDTH + meio - y + 1);
			echochar('|');
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
		move(meio + 1, meio + 1);
		echochar('o');
	}

	if(massa >= 60){
		move(meio + 1, meio);
		echochar('o');
	}

	if(massa >= 70){
		move(meio+1, meio - 1);
		echochar('o');
	}

	if(massa >= 80){
		move(meio, meio - 1);
		echochar('o');
	}

	if(massa >= 90){
		move(meio - 1, meio - 1);
		echochar('o');
	}
	refresh();
}

void Tela::stop() {
	endwin();
}

// funçoes auxiliares para mostrar mensagens
void Tela::menu(){
  mvaddstr(0, 0, "WELCOME TO AGAR.IO (REMASTERED)");
  mvaddstr(1, 0, "TYPE 't' TO TIME RUN");
  mvaddstr(2, 0, "TYPE 'e' TO MULTIPLAYER (SOON)");
  mvaddstr(3, 0, "TYPE 'q' TO EXIT");
}

void Tela::msg(){
	mvaddstr(5, 0, "================================================");
	mvaddstr(6, 0, "GET 100 PTS (*) AND RUN FROM ENEMIES (+) IN 30 s.");
	mvaddstr(7, 0, "================================================");
}

void Tela::vitoria_ou_derrota(int vit_der){
	clear();
	if(vit_der == 0) { mvaddstr(6, 3, "YOU LOSE!"); }
	else  {mvaddstr(6, 3, "YOU WIN!");}
}


Tela::~Tela() {
	this->stop();
	;
}
