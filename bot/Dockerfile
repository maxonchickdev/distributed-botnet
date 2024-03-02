FROM ubuntu:latest AS builder

RUN apt-get update -y && apt-get install cmake build-essential libboost-all-dev git openssl libssl-dev -y

WORKDIR /app/distribute_botnet

COPY . /app/distribute_botnet/

RUN ./compile.sh

FROM ubuntu:latest

RUN apt-get update -y && apt-get install libboost-all-dev -y

WORKDIR /app/distribute_botnet

COPY --from=builder /app /app

EXPOSE 8080

ENTRYPOINT ["./bin/bot"]
