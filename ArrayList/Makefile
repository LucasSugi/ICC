all: Array
Array: opcao.o ArrayList.o item.o main.o
	gcc -o Array opcao.o ArrayList.o -lm item.o main.o
ArrayList.o: ArrayList.c ArrayList.h
	gcc -o ArrayList.o -c ArrayList.c
item.o: item.c item.h
	gcc -o item.o -c item.c
opcao.o: opcao.c opcao.h
	gcc -o opcao.o -c opcao.c
main.o: main.c item.h ArrayList.h opcao.h
	gcc -o main.o -c main.c
zip:
	zip array.zip *.c *.h Makefile
run:
	./Array
clean:
	rm -rf *.o
	rm Array
clean_zip:
	rm array.zip
