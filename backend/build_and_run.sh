PG="-lpq -lssl -lcrypto -pthread"
GTEST="-lgtest -lgtest_main"
JSN="-ljansson"
REDIS="-lhiredis"
HASH="-ltinycrypt"
URL="-lcurl"
HTTP="-lllhttp"
JWT="-ll8w8jwt"
FLAGS=-fsanitize=address
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

SRC=$(find src -name "*.c")

if [ "$1" = "release" ]; then
   gcc globals.c main.c ${SRC} -o /bin/server ${PG} ${JSN} ${HTTP} ${URL} ${REDIS} ${HASH} ${JWT} \
	-I./include && /bin/server
elif [ "$1" = "test" ]; then
   TESTS=$(find tests -name "*.c")
   if [ "$2" = "--nodb" ]; then
       TESTS=$(IFS=' '; echo "$TESTS" | grep -v "database_connectivity")
       SRC=$(IFS=' '; echo "$SRC" | grep -v "database_connectivity" | grep -v "client_interaction")
       PG=""
   fi
   g++ globals.c ${TESTS} ${SRC} -o /bin/server ${PG} ${GTEST} ${JSN} ${HTTP} ${URL} ${REDIS} ${HASH} ${JWT} \
	-I./include ${FLAGS} && /bin/server
else
 echo "Usage: build_and_run.sh release|test [--nodb]"
 exit 1
fi
