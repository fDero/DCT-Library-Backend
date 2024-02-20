cd %~dp0
cd ../..
rmdir /s /q postgres_test_volume
docker-compose -f Docker-compose.test.yaml up