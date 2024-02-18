FROM ubuntu:latest

WORKDIR /server

COPY . /server

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome
ENV DOCKERIZE_VERSION v0.7.0

RUN apt-get update
RUN apt-get install -y wget

RUN wget https://github.com/jwilder/dockerize/releases/download/${DOCKERIZE_VERSION}/dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && tar -C /usr/local/bin -xzvf dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && rm dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz

RUN apt-get install -y gcc
RUN apt-get install -y git
RUN apt-get install -y locate
RUN apt-get install -y ranger
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y make
RUN apt-get install -y postgresql-all
RUN apt-get install -y libpq-dev

EXPOSE 5432
EXPOSE 5433
EXPOSE 8080
EXPOSE 9000

CMD ["/bin/bash"]
