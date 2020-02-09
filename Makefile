all:
	gcc -o s-monitor s-monitor.c -Wall -lpcre -lncurses -lcurses -ggdb
