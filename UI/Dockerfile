FROM node:18-alpine

WORKDIR /app

COPY package.json .

RUN npm i -g pnpm

RUN pnpm i

COPY . .

EXPOSE 5173

CMD [ "pnpm", "run", "dev" ]