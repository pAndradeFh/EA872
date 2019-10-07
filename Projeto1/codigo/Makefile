FLAGS=-lncurses -lpthread -std=c++11

all: model

model: main.cpp oo.cpp modelos.hpp comida.cpp gameController.cpp player.cpp fisica.cpp
	g++ -omodel main.cpp oo.cpp comida.cpp gameController.cpp player.cpp fisica.cpp $(FLAGS)
	./model
