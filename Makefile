all: test.o test.exe

test.o: test.cpp
	g++ -m32 -c test.cpp -o test.o

test.exe: test.o	
	g++ -m32 test.o -o test.exe

clean:
	rm -f *.o all
	rm -f *.exe all
