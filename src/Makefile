CXX = g++
CFLAGS = -Wall

LIBS = $(shell pkg-config --libs glu freeglut)
INCLUDES += -I../lib -I.
LIBPATH = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL 
OBJPATH = ../obj

MODELS = $(wildcard model/*.cpp)
MODELOBJ = $(patsubst model/%.cpp,$(OBJPATH)/%.o,$(MODELS))
OBJS = $(patsubst %.cpp,$(OBJPATH)/%.o,$(wildcard *.cpp))
PROGRAM = ../McDonald

RM = rm -rf

ifeq ($(shell uname), Darwin)
	LIBS = $(LIBPATH) $(FRAMEWORK)
	CFLAGS = -w
endif

$(shell test -d $(OBJPATH) || mkdir -p $(OBJPATH))

.PHONY: clean $(TARGETS)

all: $(PROGRAM)

$(PROGRAM): $(MODELOBJ) $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(MODELOBJ): $(OBJPATH)/%.o: model/%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(OBJS): $(OBJPATH)/%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDES)

clean:
	$(RM) $(PROGRAM) $(OBJPATH)