CXX = g++
CFLAGS = -Wall
LIBS = $(shell pkg-config --libs glu freeglut)
LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL 
BIN = ./bin
OBJ = ./obj
SRC = $(filter-out main.cpp,$(wildcard *.cpp))
PROGRAM = $(BIN)/McDonald
PROGRAMS = $(patsubst %.cpp,$(BIN)/%,$(SRC))
TARGETS = $(patsubst %.cpp,%,$(SRC))
RM = rm -rf
CP = cp -f

$(shell test -d $(BIN) || mkdir -p $(BIN))
$(shell test -d $(OBJ) || mkdir -p $(OBJ))

ifeq ($(shell uname), Darwin)
	LIBS = $(LIBPATH) $(FRAMEWORK)
	CFLAGS = -w
endif

.PHONY: clean $(TARGETS)

all: $(PROGRAM)

$(TARGETS): %: $(BIN)/%

$(PROGRAM): $(patsubst %,$(OBJ)/%.o,$(TARGETS)) $(OBJ)/main.o
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(PROGRAMS): $(BIN)/%: $(OBJ)/%.o $(OBJ)/main.o
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJ)/%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(OBJ) $(BIN)