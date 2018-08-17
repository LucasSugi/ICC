all: 
	gcc src/*.c -lm -I./includes -g -o build/main
	
run:
	valgrind --leak-check=full ./build/main

clean:
	rm -r build/main
