/*
	Paulo Roberto Andrade Filho - LAB4. RA156951
*/
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>
#include <portaudio.h>
#include <vector>


class Corpo {
  private:
  float massa;
  float velocidade;
  float posicao;
  float aceleracao;
  float amortecimento;
  float constante_mola;

  public:
  Corpo(float massa, float velocidade, float posicao, float amortecimento, float constante_mola);
  void update(float nova_velocidade, float nova_posicao, float nova_aceleracao);
  float get_massa();
  float get_velocidade();
  float get_posicao();
  float get_aceleracao();
  float get_constante_mola();
  float get_amortecimento();
};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};

class Fisica {
  private:
    ListaDeCorpos *lista;

  public:
    Fisica(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void update(float deltaT);
    void adicionaForca(float deltaT, float novaForca);
};

class Tela {
  private:
    ListaDeCorpos *lista, *lista_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void update();
};

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};


namespace Audio {

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};


class Player {
  private:
    Sample *audio_sample;
    bool playing;

    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    PaTime              streamOpened;


  public:
    Player();
    ~Player();

    void init();
    void pause();
    void stop();
    void play(Sample *audiosample);
    Sample *get_data();
};

}

#endif
