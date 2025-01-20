FROM debian:11

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    libboost-all-dev

COPY . /app
WORKDIR /app/server

RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8082

CMD ["./build/TimeServer"]