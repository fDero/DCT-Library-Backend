
PG := -lpq -lssl -lcrypto -pthread
GTEST := -lgtest -lgtest_main
JSN := -lcjson
HTTP := -lhttp_parser

ALL_SRC := $(shell find src -name "*.c")
NODB_SRC := $(filter-out src/database_connectivity/%,$(wildcard src/*.c src/*/*.c))

ALL_TESTS := $(shell find tests -name "*.c")
NODB_TESTS := $(filter-out tests/database_connectivity/%,$(wildcard tests/*.c tests/*/*.c))

build_and_run:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	gcc main.c $(ALL_SRC) -o /bin/server $(PG) $(JSN) $(HTTP) -I./include
	/bin/server

test:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	g++ $(ALL_TESTS) $(ALL_SRC) -o /bin/server $(PG) $(GTEST) $(JSN) $(HTTP) -I./include -fsanitize=address
	/bin/server

test-nodb:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	g++ $(NODB_TESTS) $(NODB_SRC) -o /bin/server $(GTEST) $(JSN) $(HTTP) -I./include -fsanitize=address
	/bin/server