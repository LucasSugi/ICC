all: clean
	mkdir build
	mkdir result
	gcc src/*.c -I./includes -o build/main
	./build/main > result/result.txt 
clean:
	rm -rf build
	rm -rf result
	find -name "*~" -exec rm -rf {} \;
