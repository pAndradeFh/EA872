#ifndef FISICA_HPP
#define FISICA_HPP

class Fisica {
  private:
    Player *jogador;
		float max_vel;

  public:
    Fisica(Player *jogador, float max_vel);
		void update(float deltaT);
		void aplica_forca(float deltaT, float forca_x, float forca_y);
};

#endif
