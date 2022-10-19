FICHIERS_C=$(wildcard *.cpp)	
EXEC=acab

all: $(FICHIERS_C) $(EXEC)
	./$(EXEC)

$(EXEC): $(FICHIERS_C)
	g++ $(FICHIERS_C) -o $(EXEC)
