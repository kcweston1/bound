exe:	src/main.cpp
	g++ src/*.cpp -Isrc -std=c++17

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out