FLAGS=-lncurses -lpthread -std=c++11

all: model

model: model_mainloop.cpp oo_model.cpp oo_model.hpp listComida.cpp
	g++ -omodel model_mainloop.cpp oo_model.cpp listComida.cpp $(FLAGS)
	./model
