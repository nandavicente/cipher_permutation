CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC = src
OBJ = $(SRC)/main.cpp $(SRC)/cipher.cpp $(SRC)/frequency.cpp $(SRC)/utils.cpp

all: cifra

cifra: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o cifra

clean:
	rm -f cifra
