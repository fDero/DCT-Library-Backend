
gcc main.c src/*.c -o server -lpq -lssl -lcrypto -pthread -I./include
./server

