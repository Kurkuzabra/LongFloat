all: main.o main.exe

main.o: main.c
	gcc -m32 -c main.c -o main.o

main.exe: main.o	
	gcc -m32 main.o -o main.exe

clean:
	rm -f *.o all
	rm -f *.exe all

# add.o: add.asm
# 	echo "Did nothing"
