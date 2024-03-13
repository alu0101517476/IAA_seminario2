# CXX = g++ -DNDEBUG -O3 main.cpp -I./smile -L./smile -lsmile

# SRC = main.cpp  # Agrega main.cpp aquí
# OBJ = $(SRC:.cpp=.o)
# EXEC = BOT

# all: $(EXEC)

# $(EXEC): $(OBJ) main.o  # Agrega main.o aquí
# 	$(CXX) $(LDFLAGS) -o $@ $(OBJ) main.o

# clean:
# 	rm -rf $(OBJ) $(EXEC)

do:
	g++ -DNDEBUG -O3 main.cpp -I./smile -L./smile -lsmile