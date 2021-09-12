install: config.c
	gcc config.c -o configmaker
	mkdir -p ~/.config/i3
	./configmaker >~/.config/i3/config
