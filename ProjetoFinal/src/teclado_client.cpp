#include "teclado_client.hpp"
#include <iostream>
#include <ncurses.h>
void threadfun (char *keybuffer, int *control)
{
  char c;
  while ((*control) == 1) {
    c = getch();
    if (c!=ERR) (*keybuffer) = c;
    else (*keybuffer) = 0;
    std::this_thread::sleep_for (std::chrono::milliseconds(10));
  }
  return;
}

Teclado_Client::Teclado_Client() {}
Teclado_Client::~Teclado_Client() {}

void Teclado_Client::init() {
    raw();
    keypad(stdscr, TRUE);
    initscr();
    noecho();
    curs_set(0);
    this->rodando = 1;
    std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
    (this->kb_thread).swap(newthread);
}

void Teclado_Client::stop() {
  this->rodando = 0;
  (this->kb_thread).join();
}

char Teclado_Client::getchar() {
    char c = this->ultima_captura;
    this->ultima_captura = 0;
    return c;
}
