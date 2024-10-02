CC := gcc

EXEC := programa-principal
CFLAGS := -Wall -g -Og -std=gnu99 -Wextra -pedantic -O2 -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS := `pkg-config --libs glib-2.0` -lm 

SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@ ; echo "[Compiling] $@"

build/%.o: src/%.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@ ; echo "[Linking] $@"

.PHONY: clean
clean:
	rm -rf build/*
	rm -f programa-principal
