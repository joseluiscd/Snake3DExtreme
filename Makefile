CXX_FLAGS = -g -std=c++11 -D_GLIBCXX_DEBUG
LD_FLAGS = -lSDL2 -lGL -lGLU -lSDL2_image
OBJECTS = main.o cgvInterfaceSDL.o cgvViewport.o cgvCamera.o cgvPoint3D.o cgvScene.o cgvColor.o cgvLight.o cgvMaterial.o cgvTexture.o snake/snake.o snake/labyrinth.o
CXX = g++
.PHONY: run clean

all: run

%.o: %.cpp %.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(LD_FLAGS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LD_FLAGS)

run: build
	./build

clean:
	rm -f *.o build
