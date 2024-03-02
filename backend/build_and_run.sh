#! /bin/bash

LOGO_COLOR="\033[33m"

#$(printf ${LOGO_COLOR})
stdbuf -o0 cat << EOF
$(printf ${LOGO_COLOR}) ________  ________ _________        ___       ___  ________  ________  ________  ________      ___    ___ 
$(printf ${LOGO_COLOR})|\   ___ \|\   ____\\\\___   ___\     |\  \     |\  \|\   __  \|\   __  \|\   __  \|\   __  \    |\  \  /  /|
$(printf ${LOGO_COLOR})\ \  \_|\ \ \  \___\|___ \  \_|     \ \  \    \ \  \ \  \|\ /\ \  \|\  \ \  \|\  \ \  \|\  \   \ \  \/  / /
$(printf ${LOGO_COLOR}) \ \  \ \\\\ \ \  \       \ \  \       \ \  \    \ \  \ \   __  \ \   _  _\ \   __  \ \   _  _\   \ \    / / 
$(printf ${LOGO_COLOR})  \ \  \_\\\\ \ \  \____   \ \  \       \ \  \____\ \  \ \  \|\  \ \  \\\\\  \\\\ \  \ \  \ \  \\\\  \    \/  /  /  
$(printf ${LOGO_COLOR})   \ \_______\ \_______\  \ \__\       \ \_______\ \__\ \_______\ \__\\\\ _\\\\ \__\ \__\ \__\\\\ _\ __/  / /    
$(printf ${LOGO_COLOR})    \|_______|\|_______|   \|__|        \|_______|\|__|\|_______|\|__|\|__|\|__|\|__|\|__|\|__|\___/ /     
$(printf ${LOGO_COLOR})                                                                                              \|___|/      
                                                                                                                                                                                                                                                                                                                                 
EOF

if [ "$1" = "test" ]; then
	TEST_COLOR="\033[32m"
	cat << EOF
$(printf ${TEST_COLOR})  _____ ___ ___ _____ ___ 
$(printf ${TEST_COLOR}) |_   _| __/ __|_   _/ __|
$(printf ${TEST_COLOR})   | | | _|\__ \ | | \__ \\
$(printf ${TEST_COLOR})   |_| |___|___/ |_| |___/                         
                                                                 
EOF
fi

stdbuf -o0 printf "\x1b[0m"

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
