FROM alpine:latest

RUN apk update && apk add cmake make g++ boost-dev git asio-dev

WORKDIR /app/distribute_botnet/bots/

COPY . /app/distribute_botnet/bots/bot/

RUN mkdir -p build

WORKDIR /app/distribute_botnet/bots/bot/build/

RUN cmake .. && cmake --build .

EXPOSE 8080

ENTRYPOINT ["./bot"]
