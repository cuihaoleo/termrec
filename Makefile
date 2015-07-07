CC=gcc

chattr_helper: chattr_helper.c
	$(CC) -o $@ $^

setcap: chattr_helper
	chmod +x $^
	setcap CAP_LINUX_IMMUTABLE+ep $^

clean:
	rm -f chattr_helper

