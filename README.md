# distributed-botnet

### Up ui
```
docker run -p 5173:5173 <ui_image>:<tag>
```

### Up master
```
docker run --net=bridge -p 8080:8080 --name master <master_image>:<tag>
```

### Up bot
```
docker run --net=host --name bot_<no> <bot_image>:<tag>
```
