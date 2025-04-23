CC = g++
CFLAGS = -Iinclude
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
OUT = main

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(OUT)


