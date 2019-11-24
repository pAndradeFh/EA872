#ifndef GC_HPP
#define GC_HPP

#include "player.hpp"
#include "comida.hpp"

class GameController {
	private:
		Enemy * get_enemy();
	public:
		ListComida *lista_de_comidas;
		Player *jogador;
		Enemy *enemy;
		GameController(ListComida *lista_de_comidas, Player *ldc, Enemy *enemy);
		int verifica_e_realiza_captura();
};

#endif
