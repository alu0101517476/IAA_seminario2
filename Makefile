CXX = g++
CXXFLAGS = -DNDEBUG -O3 -I./smile -g 
LDFLAGS = -L./smile -lsmile -fsanitize=address

SRC = main.cpp  # Agrega main.cpp aquí
OBJ = $(SRC:.cpp=.o)
EXEC = BOT

all: $(EXEC)

$(EXEC): $(OBJ) main.o  # Agrega main.o aquí
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) main.o

clean:
	rm -rf $(OBJ) $(EXEC)
