#include <chrono>
#include "player.hpp"
#include <ncurses.h>
using namespace std::chrono;

#define WIDTH 20
#define HEIGTH 30
#define SCREEN 11

int Enemy::get_x(){
  return this->x;
}

int Enemy::get_y(){
  return this->y;
}

Enemy::Enemy(int x, int y){
  this->x = x;
  this->y = y;
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
