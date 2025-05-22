FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome
ENV DOCKERIZE_VERSION v0.7.0

RUN apt-get update

RUN apt-get install -y wget
RUN apt-get install -y gcc
RUN apt-get install -y gpp
RUN apt-get install -y git
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y make
RUN apt-get install -y valgrind

RUN mkdir /trash
RUN mkdir /auth_keys

RUN wget https://github.com/nodejs/llhttp/archive/refs/tags/release/v9.2.0.tar.gz  \
	&& tar -xzf v9.2.0.tar.gz                                                      \
	&& cd llhttp-release-v9.2.0                                                    \
	&& mkdir build && cd build && cmake .. && make                                 \
	&& mv libllhttp.so.9.2.0 /usr/local/lib                                        \
	&& ln -s /usr/local/lib/libllhttp.so.9.2.0 /usr/local/lib/libllhttp.so         \
	&& ln -s /usr/local/lib/libllhttp.so.9.2.0 /usr/local/lib/libllhttp.so.9.2     \
	&& mv ../include/llhttp.h /usr/include                                         \
	&& cd /                                                                        \
	&& mv /llhttp-release-v9.2.0 /trash                                            \
	&& mv /v9.2.0.tar.gz /trash

RUN git clone https://github.com/intel/tinycrypt \
    && cd tinycrypt                              \
    && make                                      \         
    && cp -r lib/include/tinycrypt /usr/include  \
    && cp lib/libtinycrypt.a /usr/lib            \
    && cd /                                      \
    && mv tinycrypt /trash

RUN wget https://github.com/GlitchedPolygons/l8w8jwt/releases/download/2.3.2/l8w8jwt-2.3.2-linux-x86_64.tar.gz \
	&& tar -xzf l8w8jwt-2.3.2-linux-x86_64.tar.gz                               \
	&& mv l8w8jwt/bin/release/libl8w8jwt.so.2.3.2 /usr/local/lib                \
	&& ln -s /usr/local/lib/libl8w8jwt.so.2.3.2 /usr/local/lib/libl8w8jwt.so    \
	&& ln -s /usr/local/lib/libl8w8jwt.so.2.3.2 /usr/local/lib/libl8w8jwt.so.2  \
	&& mv l8w8jwt/include/l8w8jwt /usr/include                                  \
	&& cd /                                                                     \
	&& mv l8w8jwt /trash                                                        \
	&& mv l8w8jwt-2.3.2-linux-x86_64.tar.gz /trash

RUN wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz \
	&& tar -xvzf jansson-2.14.tar.gz  \
	&& cd jansson-2.14 && ./configure \
	&& make && make install           \
	&& cd /                           \
	&& mv jansson-2.14 /trash         \
	&& mv jansson-2.14.tar.gz /trash

RUN wget https://github.com/jwilder/dockerize/releases/download/${DOCKERIZE_VERSION}/dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && tar -C /usr/local/bin -xzvf dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz \
    && mv dockerize-linux-amd64-${DOCKERIZE_VERSION}.tar.gz /trash

RUN apt-get install -y libgtest-dev 
RUN apt-get install -y locate
RUN apt-get install -y ranger
RUN apt-get install -y postgresql-all 
RUN apt-get install -y redis-server
RUN apt-get install -y libhiredis-dev   
RUN apt-get install -y libcurl4-openssl-dev	

RUN ldconfig

RUN rm -rf /trash

EXPOSE 8080

CMD ["/bin/bash"]
