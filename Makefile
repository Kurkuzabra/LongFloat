all: test.o test.exe

test.o: test.cpp
	g++ -c test.cpp -o test.o -lgtest -lpthread

test.exe: test.o
	g++  test.o -o test -lgtest -lpthread

clean:
	rm -f *.o all
	rm -f *.exe all
