cd %~dp0
cd ../..
rmdir /s /q postgres_volume
docker-compose -f Docker-compose.yaml up