PG="-lpq -lssl -lcrypto -pthread"
GTEST="-lgtest -lgtest_main"
JSN="-ljansson"
# HTTP="-lhttp_parser"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

SRC=$(find src -name "*.c")

if [ "$1" = "release" ]; then
    gcc main.c ${SRC} -o /bin/server ${PG} ${GTEST} ${JSN} ${HTTP} -I./include
elif [ "$1" = "test" ]; then
    TESTS=$(find tests -name "*.c")
    if [ "$2" = "--nodb" ]; then
        TESTS=$(IFS=' '; echo "$TESTS" | grep -v "database_connectivity")
        SRC=$(IFS=' '; echo "$SRC" | grep -v "database_connectivity")
        PG=""
    fi
    g++ ${TESTS} ${SRC} -o /bin/server ${PG} ${GTEST} ${JSN} ${HTTP} -I./include -fsanitize=address
else
  echo "Usage: build_and_run.sh release|test [--nodb]"
  exit 1
fi

/bin/server