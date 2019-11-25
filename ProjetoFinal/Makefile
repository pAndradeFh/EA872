SRC_SERVER :=  $(filter-out src/client.cpp, $(wildcard src/*.cpp))
SRC_CLIENT :=  $(filter-out src/server.cpp, $(wildcard src/*.cpp))
BIB := $(wildcard src/*.hpp)

all: server client

server: $(SRC_SERVER) $(BIB)
	g++ $(SRC_SERVER) -o server -std=gnu++11 -lncurses -lpthread -lportaudio

client: $(SRC_CLIENT) $(BIB)
	g++ $(SRC_CLIENT) -o client -std=c++11 -lncurses -lpthread -lportaudio

remove:
	rm server client
