CC		= g++
CFLAGS		= -Wall -g
LIBRARIES	= -lGL -lGLU -lglut
OBJECTS		= $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
BINARY		= netsim

all: $(OBJECTS)
	$(CC) -o $(BINARY) $(LIBRARIES) $(OBJECTS)

%.o: %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

run: all
	./$(BINARY)

debug: all
	gdb $(BINARY)

clean:
	rm -f src/*.o
	rm -f src/*~
	rm -f ./$(BINARY)
	rm -f *~
