CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp comments.cpp Player.cpp fileio.cpp Location.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TextAdventure

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

