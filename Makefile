config: config.c
	gcc config.c -o configmaker
	./configmaker >~/.config/i3/config
