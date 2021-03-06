CC = g++
CFLAGS = -c -Wall
LDFLAGS =
SOURCES = main.cpp fileio.cpp Parser.cpp Player.cpp Location.cpp Item.cpp Compiler.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = TextAdventure

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

