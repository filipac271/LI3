CC := gcc

EXEC := programa-principal
CFLAGS :=-Wall -Wextra -pedantic -O2 -Iinclude 

#LDFLAGS :=`pkg-config --libs glib-2.0` -lm Quando começarmos a usar as bibliotecas mexemos nisto


SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(CFLAGS)  $^ -o $@ ; echo "[Compiling] $@"

build/%.o: src/%.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@ ; echo "[Linking] $@"

.PHONY: clean
clean:
	rm -rf build/*
	rm -f programa-principal


