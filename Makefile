CXX_FLAGS = -std=c++11
LD_FLAGS = -lSDL2 -lGL -lGLU
OBJECTS = main.o cgvInterfaceSDL.o cgvViewport.o cgvCamera.o cgvPoint3D.o cgvScene.o cgvColor.o cgvLight.o cgvMaterial.o snake/snake.o snake/labyrinth.o

.PHONY: run clean

all: run

%.o: %.cpp %.h
	g++ -std=c++11 -c $< -o $@ $(LD_FLAGS)

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@ $(LD_FLAGS)

build: $(OBJECTS)
	g++ -std=c++11 $^ -o $@ $(LD_FLAGS)

run: build
	./build

clean:
	rm -f *.o build
