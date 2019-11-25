#ifndef GC_HPP
#define GC_HPP

#include "player.hpp"
#include "comida.hpp"
#include <fstream>
#include <iostream>
#include <string>

class GameController {
	private:
		std::vector<Player*> *jogadores;
	public:
		ListComida *lista_de_comidas;
		GameController(ListComida *lista_de_comidas);
		std::vector<Player*> *getJogadores();
		void addRandomJogador(int height, int width);
		int verifica_e_realiza_captura();
		std::string serialize();
};

#endif
