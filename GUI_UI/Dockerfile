FROM alpine:latest

RUN apk add gcc g++ cmake g++ make boost-dev git mbedtls-dev mbedtls-utils asio-dev sqlite-dev

WORKDIR /GUI_UI/

COPY . /GUI_UI/

RUN tar -xvf wt-4.10.4.tar.gz

WORKDIR /GUI_UI/wt-4.10.4/

RUN mkdir -p build

WORKDIR /GUI_UI/wt-4.10.4/build/

RUN cmake .. && cmake --build .

RUN make install

# RUN ldconfig

WORKDIR /GUI_UI/

RUN g++ -std=c++14 -o main main.cpp -lwthttp -lwt

ENTRYPOINT [ "./main", "--docroot", ".", "--http-address", "0.0.0.0", "--http-port", "8080" ]
