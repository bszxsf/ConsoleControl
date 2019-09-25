#ifndef CONSOLE_H
#define CONSOLE_H 1

#include <stdint.h>

class _console{
protected:
	_console(const _console&) = delete;//If you use C++17, const console&& is recommended
	_console();
public:
	static _console& getInstance();
	void clear();
	class _color{
	protected:
		_color(const _color&) = delete;
		_color();
	public:
		static _color& getInstance();
		void reset();
		void setFront(uint8_t R, uint8_t G, uint8_t B);
		void setBack(uint8_t R, uint8_t G, uint8_t B);
	};
	_color& color = _color::getInstance();
	class _cursor{
	protected:
		_cursor(const _cursor&) = delete;
		_cursor();
	public:
		static _cursor& getInstance();
		void savePos();
		void restorePos();
		void show();
		void hide();
		class _move{
		protected:
			_move(const _color&) = delete;
			_move();
		public:
			static _move& getInstance();
			void up(const uint16_t val);
			void down(const uint16_t val);
			void right(const uint16_t val);
			void left(const uint16_t val);
			void to(const uint16_t x, const uint16_t y);
		};
		_move& move = _move::getInstance();
	};
	_cursor& cursor = _cursor::getInstance();
};

extern _console& console;

#endif

