# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g `sdl2-config --cflags` -I/usr/include/SDL2

# Linker flags
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

# Source files
SRC = src/main.c src/game.c src/file.c src/defs.c

# Output executable
OUT = chess

# Build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean object files and executable
clean:
	rm -f $(OUT)
