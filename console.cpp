#include "console.h"
#include <stdio.h>

using _color = _console::_color;
using _cursor = _console::_cursor;
using _move = _console::_cursor::_move;

//_console
//@{

_console& console = _console::getInstance();

_console::_console(){}

_console& _console::getInstance()
{
	static _console instance;
	return instance;
}

void _console::clear()
{
	printf("\033[2J");
	printf("\033[0;0H");
	fflush(stdout);
	return;
}

//@} _console

//_console::_color
//@{

_color::_color(){}

_color& _color::getInstance()
{
	static _color instance;
	return instance;
}

void _color::reset()
{
	printf("\033[0m");
	fflush(stdout);
	return;
}

void _color::setFront(uint8_t R, uint8_t G, uint8_t B)
{
	printf("\033[38;2;%d;%d;%dm", R, G, B);
	fflush(stdout);
	return;
}

void _color::setBack(uint8_t R, uint8_t G, uint8_t B)
{
	printf("\033[48;2;%d;%d;%dm", R, G, B);
	fflush(stdout);
	return;
}

//@} _console::_color

//_console::_cursor
//@{

_cursor::_cursor(){}

_cursor& _cursor::getInstance()
{
	static _cursor instance;
	return instance;
}

void _cursor::savePos()
{
	printf("\033[s");
	fflush(stdout);
	return;
}

void _cursor::restorePos()
{
	printf("\033[u");
	fflush(stdout);
	return;
}

void _cursor::show()
{
	printf("\033[?25h");
	fflush(stdout);
	return;
}

void _cursor::hide()
{
	printf("\033[?25l");
	fflush(stdout);
	return;
}

//@} _console::_cursor

//_console::_cursor::_move
//@{

_move::_move(){}

_move& _move::getInstance()
{
	static _move instance;
	return instance;
}

void _move::up(uint16_t val)
{
	printf("\033[%dA", val);
	fflush(stdout);
	return;
}

void _move::down(uint16_t val)
{
	printf("\033[%dB", val);
	fflush(stdout);
	return;
}

void _move::right(uint16_t val)
{
	printf("\033[%dC", val);
	fflush(stdout);
	return;
}

void _move::left(uint16_t val)
{
	printf("\033[%dD", val);
	fflush(stdout);
	return;
}

void _move::to(uint16_t x, uint16_t y)
{
	printf("\033[%d;%dH", y, x);
	fflush(stdout);
	return;
}

//@} _console::_cursor::_move

