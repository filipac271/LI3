CC := gcc

EXEC := programa-principal
CFLAGS := -Wall -g -Og -std=gnu99 -Wextra -pedantic -Iinclude $(shell pkg-config --cflags glib-2.0) -MMD -MP
LDFLAGS := $(shell pkg-config --libs glib-2.0) -lm 

SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)
DEP := $(OBJ:.o=.d)

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ ; echo "[Compiling] $@"

-include $(DEP)

.PHONY: clean
clean:
	rm -rf build
	rm -f $(EXEC)
	rm -f resultados/*.txt
	rm -f resultados/*.csv
