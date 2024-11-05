CC := gcc

EXEC := programa-principal
CFLAGS := -Wall -g -Og -O2 -std=gnu99 -Wextra -pedantic -Iinclude $(shell pkg-config --cflags glib-2.0) -MMD -MP
LDFLAGS := $(shell pkg-config --libs glib-2.0) -lm 

SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)


EXEC_TEST := programa-testes
CFLAGS_TEST := $(CFLAGS) -Wno-unused-function




DEP := $(OBJ:.o=.d)

.PHONY: all
all: $(EXEC) $(EXEC_TEST)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ ; echo "[Compiling] $@"


$(EXEC_TEST): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS_TEST) -c $< -o $@ ; echo "[Compiling] $@"



-include $(DEP)

.PHONY: clean
clean:
	rm -rf build
	rm -f $(EXEC)
	rm -f $(EXEC_TEST)
	rm -f resultados/*.txt
	rm -f resultados/*.csv