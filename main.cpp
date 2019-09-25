#include "console.h"
#include "tty_control.h"
#include <signal.h>
#include <cstdio>
#include <cstdlib>

void sighandler(int signum)
{
	console.color.reset();
	console.cursor.show();
	tty.key.end();
	console.clear();
	exit(0);
	return;
}


int main()
{
	signal(SIGINT, sighandler);
	int key = KEY_NONE;
	int ret;
	if (ret = tty.key.init() < 0) return 1;
	console.clear();
	console.cursor.hide();
	console.color.setFront(0, 0, 0);
	console.color.setBack(255, 255, 255);
	printf("  ");
	console.cursor.move.left(2);
	console.color.reset();
	while (key != KEY_ESC) {
		key = tty.key.getKey();
		//printf("%d\n", key);
		switch (key) {
		case KEY_UP:
			printf("  ");
			console.color.setBack(255, 255, 255);
			console.cursor.move.left(2);
			console.cursor.move.up(1);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
			break;
		case KEY_DOWN:
			printf("  ");
			console.color.setBack(255, 255, 255);
			console.cursor.move.left(2);
			console.cursor.move.down(1);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
			break;
		case KEY_LEFT:
			printf("  ");
			console.color.setBack(255, 255, 255);
			console.cursor.move.left(4);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
			break;
		case KEY_RIGHT:
			printf("  ");
			console.color.setBack(255, 255, 255);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
			break;
		case 's':
			console.cursor.savePos();
			//console.cursor.restorePos();
			break;
		case 'u':
			printf("  ");
			console.cursor.restorePos();
			console.color.setBack(255, 255, 255);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
			break;
		case 'r':
			console.clear();
			console.color.setBack(255, 255, 255);
			printf("  ");
			console.color.reset();
			console.cursor.move.left(2);
		}
	}
	console.color.reset();
	tty.key.end();
	console.cursor.show();
	console.clear();
	return 0;
}
