FROM ubuntu:latest

WORKDIR /server

COPY . /server

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome
ENV DOCKERIZE_VERSION v0.7.0

RUN apt-get update

RUN apt-get install -y redis-server
RUN apt-get install -y libhiredis-dev
RUN apt-get install -y wget
RUN apt-get install -y gcc
RUN apt-get install -y gpp
RUN apt-get install -y git
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y make

# RUN apt-get install -y software-properties-common
# RUN add-apt-repository ppa:ben-collins/libjwt 
# RUN apt-get update && apt-get install -y libjwt-dev

# RUN git clone https://github.com/DaveGamble/cJSON && cd cJSON && mkdir build && cd build && cmake .. && cd .. && make && make install

# RUN git clone https://www.github.com/nodejs/http-parser && cd http-parser && make && make install

RUN git clone https://github.com/intel/tinycrypt \
    && cd tinycrypt                              \
    && make                                      \         
    && cp -r lib/include/tinycrypt /usr/include  \
    && cp lib/libtinycrypt.a /usr/lib

RUN wget https://github.com/GlitchedPolygons/l8w8jwt/releases/download/2.3.2/l8w8jwt-2.3.2-linux-x86_64.tar.gz \
		&& tar -xzf l8w8jwt-2.3.2-linux-x86_64.tar.gz \
		&& mv l8w8jwt/bin/release/libl8w8jwt.so.2.3.2 /usr/local/lib \
		&& ln -s /usr/local/lib/libl8w8jwt.so.2.3.2 /usr/local/lib/libl8w8jwt.so \
		&& ln -s /usr/local/lib/libl8w8jwt.so.2.3.2 /usr/local/lib/libl8w8jwt.so.2 \
		&& mv l8w8jwt/include/l8w8jwt /usr/include \
		&& ldconfig \
		&& rm l8w8jwt-2.3.2-linux-x86_64.tar.gz \
		&& rm -rf l8w8jwt

RUN wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz && tar -xvzf jansson-2.14.tar.gz && cd jansson-2.14 && ./configure && make && make install

RUN wget https://github.com/jwilder/dockerize/releases/download/${DOCKERIZE_VERSION}/dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && tar -C /usr/local/bin -xzvf dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && rm dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz

RUN apt-get install -y libgtest-dev 
RUN apt-get install -y locate
RUN apt-get install -y ranger
RUN apt-get install -y postgresql-all                 

EXPOSE 5432
EXPOSE 5433
EXPOSE 8080
EXPOSE 9000

CMD ["/bin/bash"]
