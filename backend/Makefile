
PG := -lpq -lssl -lcrypto -pthread
GTEST := -lgtest -lgtest_main
JSN := -lcjson
HTTP := -lhttp_parser

build_and_run:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	gcc main.c src/*.c -o /bin/server $(PG) $(JSN) $(HTTP) -I./include
	/bin/server

test:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	g++ tests/*.cpp tests/*.c src/*.c -o /bin/server $(PG) $(GTEST) $(JSN) $(HTTP) -I./include -fsanitize=address
	/bin/server