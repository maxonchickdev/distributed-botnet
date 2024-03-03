FROM alpine:latest

RUN apk --no-cache add sqlite

WORKDIR /db

COPY demo.db /db/

CMD ["sqlite3", "./demo.db"]