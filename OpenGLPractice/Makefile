# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -Iinclude/glad
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

# Sources
CPP_FILES = main.cpp
C_FILES = src/glad.c

OBJ = $(CPP_FILES:.cpp=.o) $(C_FILES:.c=.o)
OUT = main

all: $(OUT)

# Linking
$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile C++ sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C sources
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)

