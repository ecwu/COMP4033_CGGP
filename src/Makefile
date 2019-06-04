CXX = g++
CFLAGS = -Wall

LIBS = $(shell pkg-config --libs glu freeglut)
LIBS += -I../lib -I.
LIBPATH = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
LIBPATH += -I../lib -I.
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL 

MODELS = $(wildcard model/*.cpp)
PROGRAM = ../McDonald

RM = rm -f

ifeq ($(shell uname), Darwin)
	LIBS = $(LIBPATH) $(FRAMEWORK)
	CFLAGS = -w
endif

.PHONY: clean $(TARGETS)

all: $(PROGRAM)

$(PROGRAM): $(MODELS) $(filter-out cola_texture.cpp,$(wildcard *.cpp))
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(RM) $(PROGRAM)