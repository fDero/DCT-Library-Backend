
build_and_run:
	gcc main.c src/*.c -o server -lpq -lssl -lcrypto -pthread -I./include
	./server

test:
	gcc tests/*.c src/*.c -o server -lpq -lssl -lcrypto -pthread -I./include
	./server
