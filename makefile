CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp player.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TextAdventure

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

