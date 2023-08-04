CC=g++
CFLAGS=-c -Wall -Iinclude -g
LDFLAGS=
SOURCES = $(wildcard src/*.cpp)
OBJECTS=$(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p build
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build $(EXECUTABLE)
	