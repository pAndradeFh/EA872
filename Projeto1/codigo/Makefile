FLAGS=-lncurses -lpthread -std=c++11

all: model

model: model_mainloop.cpp oo_model.cpp oo_model.hpp listComida.cpp gameController.cpp player.cpp fisica.cpp
	g++ -omodel model_mainloop.cpp oo_model.cpp listComida.cpp gameController.cpp player.cpp fisica.cpp $(FLAGS)
	./model
