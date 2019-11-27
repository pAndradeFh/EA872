#include <chrono>
#include "player.hpp"
#include <ncurses.h>
#include <string>
#include <cstring>
#include <vector>
using namespace std::chrono;

#define WIDTH 50
#define HEIGTH 50
#define SCREEN 11

ListPlayers::ListPlayers() {
	this->jogadores = new std::vector<Player *>(0);
}

std::vector<Player*> *ListPlayers::getJogadores() {
	return this->jogadores;
}

void ListPlayers::addPlayer(int width, int height) {
	std::vector<Player*> *lp = this->getJogadores();
  int aux = 0;
  int xrand, yrand;
  while(aux == 0) {
    aux = 1;
    xrand = rand() % (height - 1) + 1;
    yrand = rand() % (width - 1) + 1;
    for (int k=0;k<(lp)->size();k++){
      if(xrand==(*lp)[k]->get_x() && yrand==(*lp)[k]->get_y()){
        aux = 0;
      }
    }
  }
  Player *jog = new Player(20, xrand, yrand, 0, 0, 0, 0, 0);
  lp->push_back(jog);
}

void ListPlayers::addPlayer(Player *jog) {
  this->jogadores->push_back(jog);
}

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

Player::Player(float x, float y) {
	this->posicao_x = x;
	this->posicao_y = y;
}

Player::Player(float massa, float x, float y) {
	this->posicao_x = x;
	this->massa = massa;
	this->posicao_y = y;
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
