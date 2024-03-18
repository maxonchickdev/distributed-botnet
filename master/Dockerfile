FROM alpine:latest

RUN apk update && apk add cmake g++ make boost-dev git mbedtls-dev mbedtls-utils asio-dev sqlite-dev

WORKDIR /app/distribute_botnet/master/

COPY . /app/distribute_botnet/master/

RUN mkdir -p build

WORKDIR /app/distribute_botnet/master/build/

RUN cmake .. && cmake --build .

EXPOSE 8080

ENTRYPOINT ["./master"]
