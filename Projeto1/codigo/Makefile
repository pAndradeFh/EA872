SRC := $(wildcard src/*.cpp)
BIB := $(wildcard src/*.hpp)
EXE = agario

all: $(EXE)

$(EXE): $(SRC) $(BIB)
	g++ $(SRC) -o $(EXE) -std=c++11 -lncurses -lpthread -lportaudio
