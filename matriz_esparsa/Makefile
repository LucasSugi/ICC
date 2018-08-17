all: clean
	mkdir build
	gcc src/*.c -I./includes -g -o build/main
	valgrind ./build/main
clean:
	rm -rf build
