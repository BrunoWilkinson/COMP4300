# to build the project
# 	$ cd dir
# 	$ make
# executable binaries should be put in dir/bin
# to run the game, you need to cd bin, and type ./sfmlgame
# but it's annoying to change the directory each time
#
# to compile and run in one command type:
# make run

# define which compiler to use
CXX := g++
OUTPUT := A2 

# compile and linker flags
CXX_FLAGS := -g -O3 -std=c++20 -Wno-unused-result
INCLUDES := -I ./src
LDFLAGS := -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL

# the source files for the ecs ga,e engine
SRC_FILES := $(wildcard src/*.cpp src/engine/imgui/*.cpp src/engine/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# all of these targets will be made if you just type make
all:$(OUTPUT)

# define the main executable requirements / command
$(OUTPUT):$(OBJ_FILES) Makefile
	$(CXX) -g $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specifies how the object files are compiled fom cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

# typing `make clean` will remove all intermediate build files
clean:
	rm -f $(OBJ_FILES)

# typing `make run` will compild and run the program
run: $(OUTPUT)
	cd bin && ./A2 && cd ..

debug: $(OUTPUT)
	gdb bin/A2

debug-visual: $(OUTPUT)
	ddd bin/A2

memory-debug: $(OUTPUT)
	valgrind bin/A2
