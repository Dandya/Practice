LIBS=$(shell bash ./script.sh)
all: test.exe

build: main.c 
	gcc main.c -o test.exe

test.exe: main.o libpushkin.so
	gcc -o test.exe main.o -ldl

libpushkin.so: pushkin.o
	gcc -shared -fPIC -o libpushkin.so pushkin.o

%.o:%.c
	gcc -c $< -o $@

run: test.exe
	./test.exe $(LIBS)

clean:
	rm -f *.o *.so *.a *.exe