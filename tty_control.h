#ifndef KEY_CONTROL_H
#define KEY_CONTROL_H 1

#define KEY_NONE      -1
#define KEY_UNKNOWN   0
#define KEY_UP        0x1b5b41
#define KEY_DOWN      0x1b5b42
#define KEY_RIGHT     0x1b5b43
#define KEY_LEFT      0x1b5b44
#define KEY_ENTER     0x0a
#define KEY_ESC       0x1b
#define KEY_BACKSPACE 0x7f

class _tty{
protected:
	_tty();
	_tty(const _tty&) = delete;
public:
	static _tty& getInstance();
	class _icanon{
	protected:
		_icanon();
		_icanon(const _icanon&) = delete;
	public:
		static _icanon& getInstance();
		int on();
		int off();
	};
	_icanon& icanon = _icanon::getInstance();
	class _key{
	protected:
		_key();
		_key(const _key&) = delete;
	public:
		static _key& getInstance();
		int init();
		int end();
		int getKey();
	};

	_key& key = _key::getInstance();
};

extern _tty& tty;

#endif

