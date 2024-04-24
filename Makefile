ifdef OS
   RM := rmdir /s /q
else
   RM := rm -rf
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
	docker compose -f docker-compose-test.yaml run backend_test sh build_and_run.sh test --nodb

down:
	docker-compose -f docker-compose-release.yaml down -v --remove-orphans
	docker-compose -f docker-compose-test.yaml down -v --remove-orphans

database-console:
	docker-compose -f docker-compose-release.yaml exec database psql -U postgres -d lsodct

build-client-docker-image:
	docker build -t lso_client:1.0 frontend/LsoClient

build-client:
	cd frontend/LsoClient && mvn package

start-client:
	java -jar frontend/LsoClient/target/LSOclient-1.0-SNAPSHOT-shaded.jar