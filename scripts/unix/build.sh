#! /bin/bash

cd "$(dirname "$0")"
cd ../..
docker build -t lso_backend:1 .