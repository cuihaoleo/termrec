# termrec
终端录屏辅助工具～

## 编译

```
make
sudo make setcap
```

## 使用

`termrec` 和 `imouto` 须放在同一个目录下。

```
./termrec
```
录屏内容保存在 `~/.termrec/`。

在启动脚本中可以这样使用：
```
termrec
[ -z $TERMREC ] && exit
```

## 重播

```
scriptreplay -t timing -s typescript
```

