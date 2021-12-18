debug:
	gcc -g -Og -o choco-debug ./src/*.c

release:
	gcc -g -O3 -o choco-release ./src/*.c

asan:
	gcc -g -Og -fsanitize=address -o choco-asan ./src/*.c

clean:
	rm ./choco-debug
	rm ./choco-release
	rm ./choco-asan
