# Distributed Botnet

## Locally setup

#### To run ui
```
cd ui/
curl -fsSL https://bun.sh/install | bash

# Manually add the directory to ~/.zshrc (or similar):
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$PATH"

bun install
bun run dev

*open http://localhost:5173/
```

#### To run master
```
cd master/
./compile.sh
./bin/master

*open http://localhost:8080/
```

#### To run bot
```
cd bot/
./compile.sh
./bin/bot
```

## Setup with docker

#### Up ui
```
docker run -p 5173:5173 <ui_image>:<tag>
```

#### Up master
```
docker run --net=bridge -p 8080:8080 --name master <master_image>:<tag>
```

#### Up bot
```
docker run --net=host --name bot_<no> <bot_image>:<tag>
```
