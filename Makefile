CC					:= g++
CARGS				:= -g -ggdb -c 
LARGS				:= -g 
INCLUDE_PATHS		:= -Iinclude/
LIBS				:= -lGLESv2 -lglfw

out					:= run

.PHONY: build run

run: build
	./$(out)

build: obj/main.o obj/window.o obj/tree.o
	$(CC) $(LARGS) -o $(out) $^ $(LIBS)

obj/main.o: src/main.cpp
	$(CC) $(CARGS) $(INCLUDE_PATHS)  -o $@ $<

obj/window.o: src/window.cpp include/window.hpp
	$(CC) $(CARGS) $(INCLUDE_PATHS)  -o $@ $<

obj/tree.o: src/tree.cpp include/tree.hpp
	$(CC) $(CARGS) $(INCLUDE_PATHS)  -o $@ $<