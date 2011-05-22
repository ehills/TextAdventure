CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Item.cpp Location.cpp Player.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Play

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

