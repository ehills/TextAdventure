CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= compiled_game.cpp Location.cpp Player.cpp Item.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Play

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

