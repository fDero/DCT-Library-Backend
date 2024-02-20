
ifdef OS
   RM := rmdir /s /q
else
   RM := rm -f
endif


build-docker-image-for-backend:
	docker build -t lso_backend:1 .

start:
	docker-compose -f docker-compose-release.yaml up

start-fresh:
	$(RM) postgres_volume
	docker-compose -f docker-compose-release.yaml up
test:
	$(RM) postgres_test_volume
	docker-compose -f docker-compose-test.yaml up
