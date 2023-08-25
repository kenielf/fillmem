# Compiler Variables
CC = clang
LIBS =
CFLAGS = -Wall -Wextra -Wpedantic -O2 $(LIBS)
LOPS = $(LIBS)

SRC = ./src
DEST = ./target
OBJS = $(shell find ./src -name '*.c' | tr '\n' ' ' | sed -e 's/\.\/src/\.\/target/g' -e 's/\.*c/\.o/g')
EXEC = $(DEST)/main

.PHONY: all build rebuild run clean format

$(DEST)/%.o: $(SRC)/%.c
	@echo $(OBJS)
	@printf "\x1b[33m ! \x1b[00m%s\n" "Compiling object files!"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

build $(EXEC): $(OBJS)
	@printf "\x1b[33m ! \x1b[00m%s\n" "Linking executable!"
	$(CC) $(LOPS) $(OBJS) -o $(EXEC)

rebuild: clean build

run: $(EXEC)
	@$(EXEC)

clean:
	@printf "\x1b[31m ! \x1b[00m%s\n" "Cleaning directory"
	rm -rf $(DEST)
