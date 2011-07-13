CC = cl
CPPFLAGS = /EHsc
SOURCES = main.cpp fileio.cpp Parser.cpp Player.cpp Location.cpp Item.cpp Compiler.cpp
OBJECTS = $(SOURCES:.cpp=.obj)
EXECUTABLE = TextAdventure

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@

clean:
	del *.exe *.obj $(EXECUTABLE)

