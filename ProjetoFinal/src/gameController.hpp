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
		GameController(ListComida *lista_de_comidas, Player *ldc);
		int verifica_e_realiza_captura();
		std::string serialize();
    void unserialize(std::string buffer_in);
    void dump();
};

#endif
