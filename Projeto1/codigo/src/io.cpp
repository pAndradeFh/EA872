#include <chrono>
#include "player.hpp"
#include "comida.hpp"
#include "io.hpp"
#include <ncurses.h>

using namespace std::chrono;

#define WIDTH 20
#define HEIGTH 30
#define SCREEN 11

/*
	Construtor Tela - cria uma nova tela
*/
Tela::Tela(Player *ldc, int largura, int comprimento, int tela_player, ListComida *lc, Enemy *enemy) {
	this->jogador = ldc;
	this->largura = largura;
	this->tela_player = tela_player;
	this->comprimento = comprimento;
	this->listaComidas = lc;
	this->enemy = enemy;
}

Enemy *Tela::get_enemy(){
	return this->enemy;
}

void Tela::init() {
	int i;
	initscr();
	if (has_colors() == FALSE) { }
	else {
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(0));
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

void Tela::update(int tempo) {
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

	char xsa[64], xsa2[64];
	std::snprintf(xsa, sizeof xsa, "%f", this->jogador->get_massa());
	mvaddstr(12, 0, xsa);
	std::snprintf(xsa2, sizeof xsa2, "%i", tempo/1000);
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
}

void Tela::stop() {
	endwin();
}

void Tela::menu(){
  mvaddstr(0, 0, "WELCOME TO AGAR.IO (REMASTERED)");
  mvaddstr(1, 0, "TYPE 't' TO TIME RUN");
  mvaddstr(2, 0, "TYPE 'e' TO MULTIPLAYER (SOON)");
  mvaddstr(3, 0, "TYPE 'q' TO EXIT");
}

void Tela::msg(){
	mvaddstr(5, 0, "================================================");
	mvaddstr(6, 0, "GET 40 PTS (*) AND RUN FROM ENEMIES (+) IN 30 s.");
	mvaddstr(7, 0, "================================================");
}

void Tela::vitoria_ou_derrota(int vit_der){
	clear();
	if(vit_der == 0) {mvaddstr(6, 3, "YOU LOSE!");}
	else  {mvaddstr(6, 3, "YOU WIN!");}
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
