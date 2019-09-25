#include "tty_control.h"
#include <termios.h>
#include <syslog.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static struct termios backup;

using _icanon = _tty::_icanon;
using _key = _tty::_key;

_tty& tty = _tty::getInstance();

//_tty
//@{

_tty::_tty(){}

_tty& _tty::getInstance()
{
	static _tty instance;
	return instance;
}

//@} _tty

//_tty::_icanon
//@{

_icanon::_icanon(){}

_icanon& _icanon::getInstance()
{
	static _icanon instance;
	return instance;
}

int _icanon::on()
{
	int ret;
	struct termios opt;
	if (ret = tcgetattr(STDIN_FILENO, &opt) < 0) {
		return ret;
	}
	opt.c_lflag |= ICANON;
	if (ret = tcsetattr(STDIN_FILENO, TCSANOW, &opt) < 0) {
		return ret;
	}
	syslog(LOG_INFO, "set_icanon called by process %d", getpid());
	return 0;
}

int _icanon::off()
{
	int ret;
	struct termios opt;
	if (ret = tcgetattr(STDIN_FILENO, &opt) < 0) {
		perror("set_icanon - tcgetattr");
		syslog(LOG_ERR, "set_icanon - tcgetattr failed at process %d", getpid());
		return ret;
	}
	opt.c_lflag &= (~ICANON);
	if (ret = tcsetattr(STDIN_FILENO, TCSANOW, &opt) < 0) {
		perror("set_icanon - tcsetattr");
		syslog(LOG_ERR, "set_icanon - tcsetattr failed at process %d", getpid());
		return ret;
	}
	syslog(LOG_INFO, "set_icanon called by process %d", getpid());
	return 0;
}

//@} _tty::_icanon

//_tty::_key
//@{

_key::_key(){}

_key& _key::getInstance()
{
	static _key instance;
	return instance;
}

int _key::init()
{
	int ret;
	if (ret = fcntl(STDIN_FILENO, F_GETFL, 0) < 0) {
		perror("init_key_control - fcntl - F_GETFL");
		syslog(LOG_ERR, "init_key_control - fcntl - F_GETFL failed at process %d", getpid());
		return ret;
	}
	if (ret = fcntl(STDIN_FILENO, F_SETFL, ret | O_NONBLOCK) < 0) {
		perror("init_key_control - fcntl - F_SETFL");
		syslog(LOG_ERR, "init_key_control - fcntl - F_SETFL failed at process %d", getpid());
		return ret;
	}
	if (ret = tcgetattr(STDIN_FILENO, &backup) < 0) {
		perror("init_key_control - tcgetattr");
		syslog(LOG_ERR, "init_key_control - tcgetattr failed at process %d", getpid());
		return ret;
	}
	struct termios opt = backup;
	opt.c_lflag &= (~ICANON);
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 1;
	opt.c_lflag |= ISIG;
	opt.c_lflag &= (~ECHO);
	opt.c_iflag &= (~IGNBRK);
	opt.c_iflag |= BRKINT;
	if (ret = tcsetattr(STDIN_FILENO, TCSANOW, &opt) < 0) {
		perror("init_key_control - tcsetattr");
		syslog(LOG_ERR, "init_key_control - tcsetattr failed at process %d", getpid());
		return ret;
	}
	syslog(LOG_INFO, "init_key_control called by process %d", getpid());
	return 0;
}

int _key::end()
{
	int ret;
	if (ret = tcsetattr(STDIN_FILENO, TCSANOW, &backup) < 0) {
		perror("end_key_control - tcsetattr");
		syslog(LOG_ERR, "end_key_control failed at process %d", getpid());
		return ret;
	}
	syslog(LOG_INFO, "end_key_control called by process %d", getpid());
	return 0;
}

int _key::getKey()
{
	char buf[8];
	int sz, i;
	int ret = 0;
	sz = read(STDIN_FILENO, buf, 8);
	if (sz <= 0) return KEY_NONE;
	for (i = 0; i < sz; ++i) {
		ret <<= 8;
		ret |= (unsigned int)buf[i];
	}
	return ret;
}

//@} _tty::_key

