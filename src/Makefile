CXX = g++
CFLAGS = -Wall

LIBS = $(shell pkg-config --libs glu freeglut)
LIBS += -I../lib -I.
LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL 

BINPATH = ../bin
OBJPATH = ../obj

MODELS = $(wildcard model/*.cpp)
PROGRAM = $(BINPATH)/McDonald
PROGRAMS = $(patsubst %.cpp,$(BINPATH)/%,$(MODELS))
TARGETS = $(patsubst %.cpp,%,$(MODELS))

RM = rm -rf

$(shell test -d $(BINPATH) || mkdir -p $(BINPATH))
$(shell test -d $(OBJPATH) || mkdir -p $(OBJPATH))

ifeq ($(shell uname), Darwin)
	LIBS = $(LIBPATH) $(FRAMEWORK)
	CFLAGS = -w
endif

.PHONY: clean $(TARGETS)

all: $(PROGRAM)

$(TARGETS): %: $(BINPATH)/%

$(PROGRAM): $(MODELS) $(wildcard *.cpp)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(PROGRAMS): $(BINPATH)/%: model/%.cpp main.cpp 
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	$(RM) $(OBJPATH) $(BINPATH)