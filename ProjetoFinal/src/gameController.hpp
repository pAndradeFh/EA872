#ifndef GC_HPP
#define GC_HPP

#include "player.hpp"
#include "comida.hpp"
#include <fstream>
#include <iostream>
#include <string>

class GameController {
	private:
		ListPlayers *lista_de_jogadores;
	public:
		ListComida *lista_de_comidas;
		GameController(ListComida *lista_de_comidas, ListPlayers *lista_de_jogadores);
		std::vector<Player*> *getJogadores();
		std::vector<int> *jogadoresAtivos();
		int verifica_e_realiza_captura();
		std::string serialize(int *ativos, int size, int tempo);
};

#endif
