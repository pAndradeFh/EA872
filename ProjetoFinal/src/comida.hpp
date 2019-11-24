#ifndef COMIDA_HPP
#define COMIDA_HPP

#include <vector>
#include <stdlib.h>

class Comida {
	private:
		int x;
		int y;
	public:
		Comida(int x, int y);
		~Comida();
		int get_x();
		int get_y();
};

class ListComida {
	private:
		std::vector<Comida*> *comidas;
	public:
		ListComida();
    void hard_copy(ListComida *ldc);
    void add_corpo(Comida *c);
		void geraListaAleatoria(int numero, int height, int width);
		std::vector<Comida *> *getComidas();
};

#endif
