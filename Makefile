all: bin/row bin/col

clean:
	rm bin/row
	rm bin/col

CC=g++
C_FLAGS=-O2 -Wall -Wextra -Isrc

INC=$(wildcard src/*.h)

bin/row: src/row.cpp $(INC)
	mkdir -p bin
	$(CC) $(C_FLAGS) $< -o $@

bin/col: src/col.cpp $(INC)
	mkdir -p bin
	$(CC) $(C_FLAGS) $< -o $@

