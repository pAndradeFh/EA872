// Paulo Roberto Andrade Filho
// RA156951
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

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



#endif
