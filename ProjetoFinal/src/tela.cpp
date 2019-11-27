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

#define WIDTH 50
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
	int parsed = 1;
	try {
  	j = json::parse(info);
	} catch(const std::exception& e){
		parsed = 0;
	}
	if(parsed) {
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
	std::snprintf(xsa2, sizeof xsa2, "%i", massa);
	std::snprintf(xsa, sizeof xsa2, "%i", massa);
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
		for (int i = 0; i < 2*meio; i++) {
			move(i, meio - y);
			echochar('|');
		}
	}

	if(right_bound >= WIDTH){
		for (int i = 0; i < 2*meio; i++) {
			move(i, WIDTH + meio - y + 1);
			echochar('|');
		}
	}

	for (int i = 0; i<lc->size(); i++) {
		if(i == posi) {
			massa = (int)((*lc)[posi]->get_massa());
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
		} else {
			int x_jog = (int)((*lc)[i]->get_x());
			int y_jog = (int)((*lc)[i]->get_y());
			int massa_jog = (int)((*lc)[i]->get_massa());

			if(x_jog - x <= meio -1 && y_jog - y <= meio-1) {
				move(x_jog - x + meio, y_jog - y + meio);
				echochar('#');
			}

			if(massa_jog >= 20 && x_jog - x - 1 <= meio-1 && y_jog - y <= meio-1){
				move(x_jog - x + meio - 1, y_jog - y + meio);
				echochar('#');
			}

			if(massa_jog >= 30 && x_jog - x - 1 <= meio-1 && y_jog - y + 1 <= meio-1){
				move(x_jog - x + meio - 1, y_jog - y + meio + 1);
				echochar('#');
			}

			if(massa_jog >= 40 && x_jog - x <= meio-1 && y_jog - y + 1 <= meio-1){
				move(x_jog - x + meio, y_jog - y + meio + 1);
				echochar('#');
			}

			if(massa_jog >= 50 && x_jog - x + 1 <= meio-1 && y_jog - y + 1 <= meio-1){
				move(x_jog - x + meio + 1, y_jog - y + meio + 1);
				echochar('#');
			}

			if(massa_jog >= 60 && x_jog - x + 1 <= meio-1 && y_jog - y <= meio-1){
				move(x_jog - x + meio + 1, y_jog - y + meio);
				echochar('#');
			}

			if(massa_jog >= 70 && x_jog - x - 1 <= meio-1 && y_jog - y - 1 <= meio-1){
				move(x_jog - x + meio -1, y_jog - y + meio -1);
				echochar('#');
			}

			if(massa_jog >= 80 && x_jog - x <= meio-1 && y_jog - y - 1 <= meio-1){
				move(x_jog - x + meio, y_jog - y + meio - 1);
				echochar('#');
			}

			if(massa_jog >= 90 && x_jog - x - 1 <= meio-1 && y_jog - y - 1 <= meio-1){
				move(x_jog - x + meio - 1, y_jog - y + meio - 1);
				echochar('#');
			}
		}
	}

	refresh();
}

void Tela::stop() {
	endwin();
}

Tela::~Tela() {
	this->stop();
	;
}
