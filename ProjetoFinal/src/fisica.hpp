#ifndef FISICA_HPP
#define FISICA_HPP

#include "player.hpp"
#include <vector>

class Fisica {
  private:
    ListPlayers *lista_de_jogadores;
		float max_vel;

  public:
    Fisica(float max_vel, ListPlayers *jogadores);
		void update(float deltaT);
		void aplica_forca(float deltaT, float forca_x, float forca_y, int pos);
};

#endif
