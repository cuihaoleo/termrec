CC=gcc

imouto: imouto.c
	$(CC) -o $@ $^

setcap: imouto
	chmod +x $^
	setcap CAP_LINUX_IMMUTABLE+ep $^

clean:
	rm -f chattr_helper

