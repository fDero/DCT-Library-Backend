#! /bin/bash

cd "$(dirname "$0")"
cd ../..
rm -rf postgres_volume
docker-compose -f Docker-compose.yaml up