CXX_FLAGS = -std=c++11
GL_FLAGS = -lSDL2 -lGL -lGLU
OBJECTS = main.o cgvInterfaceSDL.o cgvViewport.o cgvCamera.o cgvPoint3D.o cgvScene.o cgvColor.o cgvLight.o cgvMaterial.o

.PHONY: run clean

all: run

%.o: %.cpp %.h
	g++ -g $(CXX_FLAGS) -c $< -o $@ $(GL_FLAGS)

build: $(OBJECTS)
	g++ -g $(CXX_FLAGS) $^ -o $@ $(GL_FLAGS)

run: build
	./build

clean:
	rm -f *.o build
