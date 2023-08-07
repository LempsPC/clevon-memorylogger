CC=g++
CFLAGS=-c -Wall -Iinclude -g
LDFLAGS=
SOURCES = $(wildcard src/*.cpp)
OBJECTS=$(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
TEST_SOURCES = $(wildcard test/*.cpp)
TEST_OBJECTS=$(addprefix build/,$(notdir $(TEST_SOURCES:.cpp=.o)))
EXECUTABLE=main
TEST_EXECUTABLE=tester

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p build
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

test: $(TEST_SOURCES) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(filter-out build/main.o, $(OBJECTS))
	mkdir -p build
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) $(filter-out build/main.o, $(OBJECTS)) -o $@

build/%.o: test/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build $(EXECUTABLE) $(TEST_EXECUTABLE)