# DCT Library: a REST API in C

DCT Library is a project for the Operating Systems Laboratory class at Università Degli Studi di 
Napoli Federico ll, that implements a REST API written in C that uses JWT authorization with ES256,
that implements password hashing and salting, and that uses both postgresql and redis.


## Building and executing the server

What is required to build and execute the system:

- Docker
- Docker Compose

### If you have Make installed

During the project, various tasks were configured using Make, which are compatible with multiple operative systems. Having it is not required to build and execute the system, but will enable you to run these commands:

- `make build-backend-docker-image`: builds the docker image for the server, which is going to be used by Compose
- `make start`: starts the server and the required databases using Docker Compose, and more specifically using the file 'docker-compose-release.yaml'
- `make start-newdb`: same as above, but, in case a Postgres database was created in a previous execution, and its files are stored in the volume 'postgres_volume', it will delete it and reconstruct it from scratch, following the instructions specified in 'docker-compose-release.yaml'
- `make test`: starts the server in a specific configuration specified by the file 'docker-compose-test.yaml'. Which runs a series of tests using the unit testing library GTest from Google. This recreates the database each time from scratch, to ensure the consistency of the rows with those that the tests expect
- `make test-nodb`: runs the tests without creating a new database from scratch, but ignores any test which requires an interaction it
- `make down`: kills any running and orphan container for the DCT Library system
- `make database-console`: requires the database service to be already running in another terminal, and allows you to enter the postgres terminal from within its container

### If you <u>don't</u> have Make installed

If you don't have Make or you don't want to run these scripts, you can recreate their behaviour using the following commands.

- To create the backend docker image, you can run `docker build -t lso_backend:1 .`
- To run docker-compose using the release configuration, you can run `docker-compose -f docker-compose-release.yaml up`
- If you want to delete the postgres volume, you will need to remove the directory 'postgres_volume'
- To run the tests, first delete the postgres volume if it is present, and then run `docker-compose -f docker-compose-test.yaml up`
- If you want to run the tests, ignoring anything related to the database and cache, run `docker compose -f docker-compose-test.yaml run backend_test sh build_and_run.sh test --nodb`
- To stop any running containers (including orphan containers) related to the DCT Library system, run both `docker-compose -f docker-compose-release.yaml down -v --remove-orphans` and `docker-compose -f docker-compose-test.yaml down -v --remove-orphans`
- If you want to enter the postgres console while the service is running, run `docker-compose -f docker-compose-release.yaml exec database psql -U postgres -d lsodct`

### Additional execution parameters
In the docker-compose files, numerous environment variables are specified. Some of them affect the behaviour of the server, while some of them are needed to run different **debug configurations**, more specifically:

- `FSANITIZE_ENABLED`: setting this to true will add the -fsanitize=address flag to compilation, enabling memory leak detection
- `DEBUG_ENABLED`: to be used along with the previous parameter, setting this to true, specifically for the release configuration, will cause the server to stop after the first client connection is closed, allowing the memory leak detection tools to show their reports
