/*
	Paulo Roberto Andrade Filho - Laboratório 6 - RA 156951
*/
#include "teclado.hpp"
void threadfun(char *keybuffer, int *control, int *connection_fd, int *socket_fd,  socklen_t client_size, struct sockaddr_in *client) {
	char c = 0;
	*connection_fd = accept(*socket_fd, (struct sockaddr*)client, &client_size);
	while ((*control) == 1) {
		recv(*connection_fd, &c, 1, 0);
    (*keybuffer) = c;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

/*
	Construtor Teclado - cria um novo teclado
*/
Teclado::Teclado() {
}

Teclado::~Teclado() {
}

void Teclado::init() {
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
  server.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(server.sin_addr));
	if (bind(socket_fd, (struct sockaddr*)&server, sizeof(server)) != 0) {

		fprintf(stderr , "Problemas ao abrir porta\n");
		return;
		
	}
  listen(socket_fd, 2);
	this->rodando = 1;
	std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando), &(this->connection_fd), &(this->socket_fd), (socklen_t)sizeof(this->client), &(this->client));
	(this->kb_thread).swap(newthread);
}

void Teclado::stop() {
	this->rodando = 0;
	(this->kb_thread).join();
	close(socket_fd);
}

char Teclado::getchar() {
	char c = this->ultima_captura;
	this->ultima_captura = 0;
	return c;
}
