PROG = ejemplo2

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2
OBJS     = main.o ventana.o modelo.o shader.o

ifeq ($(OS),Windows_NT)
    LIBS = -lglfw3 -lglew32 -lopengl32 -lgdi32
else
    LIBS = -lglfw -lGLEW -lGL
endif

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

%.o: %.cpp ventana.h modelo.h shader.h
	$(CXX) $(CXXFLAGS) -c $<

run: $(PROG)
	./$(PROG)

clean:
	rm -f $(OBJS) $(PROG)

.PHONY: run clean
