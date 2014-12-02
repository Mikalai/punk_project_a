#ifndef _H_KEYS
#define	_H_KEYS

#include <hash_map>
#include <memory>

class Keyboard;
class Mouse;

class Keys {
public:

	static void destroy();

private:

	void setKeyboard(int key, bool state);
	bool keyboard(int key);

	void setMouse(int key, bool state) { m_mouse[key] = state; }
	bool mouse(int key) { return m_mouse[key]; }
	static Keys* instance();

private:
	std::hash_map<int, bool> m_keyboard;
	std::hash_map<int, bool> m_mouse;
	static std::unique_ptr<Keys> m_instance;
	friend class Keyboard;
	friend class Mouse;
};

class Keyboard final {
public:
	static bool get(int key) {
		return Keys::instance()->keyboard(key);
	}

	static void set(int key, bool state) {
		Keys::instance()->setKeyboard(key, state);
	}
};

class Mouse final {
public:
	static bool get(int key) {
		return Keys::instance()->mouse(key);
	}

	static void set(int key, bool state) {
		Keys::instance()->setMouse(key, state);
	}
};

#endif