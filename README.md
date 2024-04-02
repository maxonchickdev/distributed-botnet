# distributed-botnet

### Up ui
```
docker run -p 5173:5173 <ui_image>:<tag>
```
**To run UI**
```
cd ui
```
```
curl -fsSL https://bun.sh/install | bash
```
Manually add the directory to ~/.zshrc (or similar):
``` 
export BUN_INSTALL="$HOME/.bun"
``` 
```
export PATH="$BUN_INSTALL/bin:$PATH"
```

```
bun install
```
to run on localhost
```
bun run dev
```
Now you will see two URL in terminal one is localhost, the second one is network one.
**To run master**
```
cd ../master
```
```
./compile.sh
```
```
./bin/master
```
**To run bot**
```
cd ../bot
```
```
./compile.sh
```

```
./bin/bot
```
### Up master
```
docker run --net=bridge -p 8080:8080 --name master <master_image>:<tag>
```

### Up bot
```
docker run --net=host --name bot_<no> <bot_image>:<tag>
```
