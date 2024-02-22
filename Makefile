
ifdef OS
   RM := rmdir /s /q
else
   RM := rm -f
endif


COMPILER_FLAGS := -lpq -lssl -lcrypto -pthread -I./backend/include
GTEST_FLAGS := -lgtest -lgtest_main
C_TO_CPP_COMPATIBILITY := -Wno-write-strings
CJSON := -lcjson
HTTP := -lhttp_parser

build-backend-docker-image:
	docker build -t lso_backend:1 .

start:
	docker-compose -f docker-compose-release.yaml up

start-newdb:
	-$(RM) postgres_volume
	docker-compose -f docker-compose-release.yaml up

test:
	-$(RM) postgres_test_volume
	docker-compose -f docker-compose-test.yaml up

test-nodb:
	docker-compose -f docker-compose-test.yaml up

backend-build-release-local-unix:
	gcc backend/*.c backend/src/*.c -o backend/server \
	${COMPILER_FLAGS} ${CJSON} ${HTTP}

backend-build-test-local-unix:
	g++ ${C_TO_CPP_COMPATIBILITY} backend/*/*.c \
	 -o backend/server_test \
	${COMPILER_FLAGS} ${GTEST_FLAGS} ${CJSON} ${HTTP}

client-local:
	gcc frontend/*.c -o frontend/client
	./frontend/client
