exe:	src/main.cpp
	g++ src/*.cpp -lSDL2 -lSDL2_image -Isrc -std=c++17

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out
