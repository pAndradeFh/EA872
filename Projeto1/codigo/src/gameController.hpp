#ifndef GC_HPP
#define GC_HPP

#include "player.hpp"
#include "comida.hpp"

class GameController {
	public:
		ListComida *lista_de_comidas;
		Player *jogador;
		Enemy *enemy;
		GameController(ListComida *lista_de_comidas, Player *ldc, Enemy *enemy);
		void verifica_e_realiza_captura();
};

#endif
