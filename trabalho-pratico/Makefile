CC := gcc

EXEC := programa-principal

EXEC_INTERATIVO := programa-interativo

CFLAGS := -Wall -g -Og -O3 -flto -std=gnu99 -Wextra -pedantic -Iinclude $(shell pkg-config --cflags glib-2.0) -MMD -MP 
LDFLAGS := $(shell pkg-config --libs glib-2.0) -lm -lncurses

SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)

EXTERNAL_OBJ := recomenda/recomendador-linux-x86_64.o


EXEC_TEST := programa-testes
CFLAGS_TEST := $(CFLAGS) -Wno-unused-function




DEP := $(OBJ:.o=.d)

.PHONY: all
all: $(EXEC) $(EXEC_INTERATIVO) $(EXEC_TEST) 

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(EXTERNAL_OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

$(EXEC_INTERATIVO): $(OBJ)
	@$(CC) $(OBJ) $(EXTERNAL_OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ ; echo "[Compiling] $@"


$(EXEC_TEST): $(OBJ)
	@$(CC) $(OBJ) $(EXTERNAL_OBJ) $(LDFLAGS) -o $@ ; echo "[Linking] $@"

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS_TEST) -c $< -o $@ ; echo "[Compiling] $@"



-include $(DEP)

.PHONY: clean
clean:
	rm -rf build
	rm -f $(EXEC)
	rm -f $(EXEC_TEST)
	rm -f $(EXEC_INTERATIVO)
	rm -f resultados/*.txt
	rm -f resultados/*.csv