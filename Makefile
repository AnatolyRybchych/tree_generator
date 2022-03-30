CC					:= g++
CARGS				:= -g -ggdb -c 
LARGS				:= -g 
INCLUDE_PATHS		:= -Iinclude/
LIBS				:= -lGL

out					:= run

.PHONY: build run

run: build
	./$(out)

build: obj/main.o
	$(CC) $(LARGS) -o $(out) $(LIBS) $^

obj/main.o: src/main.cpp
	$(CC) $(CARGS) $(INCLUDE_PATHS)  -o $@ $<
