# MakeFiles - consist of a set of rules like:
# target: prerequisites
# 	command
# 	command
# 	command
#
# 	targets: filenames, separated by spaces
# 	commands: series of steps typically used to make targets
# 	prerequisites: filenames, seprated by spaces: files need to exist before the commands
# 									are run. Called dependencies
# 	

# CXX represents the C++ compiler
CXX = g++ 

# CXXFLAGS are flags passed to the compiler when compiling (not linking)
# 	-Wall: enables all common compiler warnings
# 	-std=c++17: Use the c++17 standard
# 	-Iinclude: Adds the include/ directory to the list of places to look for header files
# 	-Isrc: Also looks inside of the src/ for headers
CXXFLAGS = -Wall -std=c++17 -Iincludes -Isrc -g

# LDFLAGS are used during linking (when combining .o files to an executable)
# 	-lglfw: Link against GLFW
# 	-lGl, -lGLU: Core OpenGL utility libs
# 	-lX11, -lXrandr, -lXi: Required for window management on Linux
# 	-lpthread: For threading support
# 	-ldl: For dynamic loading support (used by GLFW)
LDFLAGS = -lglfw -lGL -lGLU -lX11 -lpthread -lXrandr -lXi -ldl


# Directories and Executable name
# 	SCR_DIR: Folder when .cpp lives
# 	OBJ_DIR: Where .o (object) file are stored
# 	BIN: the name of the final output executable
SRC_DIR = src
OBJ_DIR = obj
BIN = program

SRCS_CPP = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_C   = $(wildcard $(SRC_DIR)/*.c)
SRCS     = $(SRCS_CPP) $(SRCS_C)

OBJS_CPP = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS_CPP))
OBJS_C   = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_C))
OBJS     = $(OBJS_CPP) $(OBJS_C)


# Default target: make runs this
# 	When running make, it build the BIN target(game), using the rule below
all: $(BIN)

# Linking Rule
# 	This build the final executable:
# 		$@ = target name (i.e, game)
# 		$^ = all prerequistes ($(OBJS) in this case)
# 	It runs
# 		g++ obj/file1.o obj/file2.o ... -o game -lgflw -lGl ...
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compilation rule (for each .cpp file)
# 	% is a wildcard - a place holder for a "stem", like main or game
# 	@ supresses the command from being printed in the terminal
# 	Rule to compile each .cpp into .o
# 		$< = first prerequiste (the .cpp file)
# 		$@ = target (the .o file)
# 		-c: compile only (dont link yet)
# 	Ensures obj/ exists before compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -Wall -Iincludes -Isrc -c $< -o $@

run: $(BIN)
	./$(BIN)

# add a make check target + .phony targets
# Clean rule
# 	Removes:
# 		The object file directory obj/
# 		The compiled executable game
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Special Target Declaration
# 	Declares all and clean as phony targets - not actual files
.PHONY: all clean
