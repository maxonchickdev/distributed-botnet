FROM node:16-alpine

WORKDIR /app

COPY package.json .

RUN npm i -g pnpm

RUN pnpm i

COPY . /app

EXPOSE 5173

CMD [ "pnpm", "run", "dev" ]