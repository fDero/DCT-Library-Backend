#! /bin/bash

cd "$(dirname "$0")"
cd ../..
rm -rf postgres_test_volume
docker-compose -f Docker-compose.test.yaml up