# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g `sdl2-config --cflags` -Iinclude

# Linker flags
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Source files
SRC = src/main.c src/game.c src/file.c src/board.c src/pieces.c

# Output executable
OUT = chess

# Build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
