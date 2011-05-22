CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= Location.cpp Player.cpp compiled_game.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Play

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

