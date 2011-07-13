CC = cl
CPPFLAGS = /EHsc
SOURCES = Location.cpp Player.cpp compiled_game.cpp 
OBJECTS = $(SOURCES:.cpp=.obj)
EXECUTABLE = Play

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@

clean:
	del *.exe *.obj $(EXECUTABLE)

