g++ tests/queries.test.c -o server_test -lpq -lssl -lcrypto -pthread -lgtest -lgtest_main -I./include
./server_test
