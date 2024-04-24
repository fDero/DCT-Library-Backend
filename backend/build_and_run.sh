#! /bin/bash

LOGO_COLOR="\033[33m"
TEST_COLOR="\033[32m"

#$(printf ${LOGO_COLOR})
stdbuf -o0 cat << EOF

$(printf ${LOGO_COLOR}) _____   _____    ______                                 
$(printf ${LOGO_COLOR})/\  _ \`\/\  _ \`\ /\__  _\                                
$(printf ${LOGO_COLOR})\ \ \/\ \ \ \/\_\\\\/_/\ \/                                
$(printf ${LOGO_COLOR}) \ \ \ \ \ \ \/_/_  \ \ \                                
$(printf ${LOGO_COLOR})  \ \ \_\ \ \ \L\ \  \ \ \                               
$(printf ${LOGO_COLOR})   \ \____/\ \____/   \ \_\                              
$(printf ${LOGO_COLOR})    \/___/  \/___/     \/_/                              
$(printf ${LOGO_COLOR})                                                        
$(printf ${LOGO_COLOR})                                                        
$(printf ${LOGO_COLOR}) __           __                                        
$(printf ${LOGO_COLOR})/\ \       __/\ \                                       
$(printf ${LOGO_COLOR})\ \ \     /\_\ \ \____  _ __    __     _ __   __  __    
$(printf ${LOGO_COLOR}) \ \ \  __\/\ \ \  __ \/\  __\/ __ \  /\  __\/\ \/\ \   
$(printf ${LOGO_COLOR})  \ \ \_\ \\\\ \ \ \ \_\ \ \ \//\ \_\ \_\ \ \/ \ \ \_\ \  
$(printf ${LOGO_COLOR})   \ \____/ \ \_\ \____/\ \_\\\\ \__/ \_\\\\ \_\  \/\____ \ 
$(printf ${LOGO_COLOR})    \/___/   \/_/\/___/  \/_/ \/__/\/_/ \/_/   \/___/  \\
$(printf ${LOGO_COLOR})                                                  /\___/
$(printf ${LOGO_COLOR})                                                  \/__/ 

EOF

if [ "$1" = "test" ]; then
	cat << EOF
$(printf ${TEST_COLOR})  _____ ___ ___ _____ ___ 
$(printf ${TEST_COLOR}) |_   _| __/ __|_   _/ __|
$(printf ${TEST_COLOR})   | | | _|\__ \ | | \__ \\
$(printf ${TEST_COLOR})   |_| |___|___/ |_| |___/                         
                                                                 
EOF
fi

stdbuf -o0 printf "\x1b[0m"

PG="-lpq"
SSL="-lssl -lcrypto"
PTHREAD="-pthread"
GTEST="-lgtest -lgtest_main"
JSN="-ljansson"
REDIS="-lhiredis"
HASH="-ltinycrypt"
URL="-lcurl"
HTTP="-lllhttp"
JWT="-ll8w8jwt"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

if [ "$FSANITIZE_ENABLED" = "true" ] ; then
   FSANITIZE="-fsanitize=address"
fi

if [ "$DEBUG_ENABLED" = "true" ] ; then
   DEBUG_MODE="--debug"
fi

SRC=$(find src -name "*.c")

if [ "$1" = "release" ]; then
   gcc main.c ${SRC} -o /bin/server ${PG} ${SSL} ${PTHREAD} ${JSN} ${HTTP} ${URL} ${REDIS} ${HASH} ${JWT} -I./include ${FSANITIZE} \
   && openssl ecparam -genkey -name prime256v1 -noout -out ${PRIVATE_KEY_FILE} > /dev/null 2>&1 \
   && openssl ec -in ${PRIVATE_KEY_FILE} -pubout -out ${PUBLIC_KEY_FILE} > /dev/null 2>&1 \
   && /bin/server ${DEBUG_MODE}
elif [ "$1" = "test" ]; then
   TESTS=$(find tests -name "*.c")
   if [ "$2" = "--nodb" ]; then
       TESTS=$(IFS=' '; echo "$TESTS" | grep -v "database_connectivity")
       SRC=$(IFS=' '; echo "$SRC" | grep -v "database_connectivity" | grep -v "client_interaction")
       PG=""
   fi
   g++ ${TESTS} ${SRC} -o /bin/server ${PG} ${SSL} ${PTHREAD} ${GTEST} ${JSN} ${HTTP} ${URL} ${REDIS} ${HASH} ${JWT} -I./include ${FSANITIZE} \
   && openssl ecparam -genkey -name prime256v1 -noout -out ${PRIVATE_KEY_FILE} > /dev/null 2>&1 \
   && openssl ec -in ${PRIVATE_KEY_FILE} -pubout -out ${PUBLIC_KEY_FILE} > /dev/null 2>&1 \
   && /bin/server ${DEBUG_MODE}
else
 echo "Usage: build_and_run.sh release|test [--nodb]"
 exit 1
fi
