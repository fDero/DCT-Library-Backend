build_and_run:
	gcc main.c src/*.c -o /bin/server -lpq -lssl -lcrypto -pthread -I./include
	/bin/server

test:
	g++ tests/*.c src/*.c -o /bin/server -lpq -lssl -lcrypto -pthread -lgtest -lgtest_main -I./include
	/bin/server