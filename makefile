exe:	src/main.cpp
	g++ src/*.cpp -lSDL2 -Isrc -std=c++17

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out
