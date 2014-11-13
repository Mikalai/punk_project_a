#ifndef _H_KEYS
#define	_H_KEYS

#include <hash_map>
#include <memory>

class Keys {
public:

	static Keys* instance();
	static void destroy();

	void setKeyboard(int key, bool state);
	bool keyboard(int key);

	void setMouse(int key, bool state) { m_mouse[key] = state; }
	bool mouse(int key) { return m_mouse[key]; }

private:
	std::hash_map<int, bool> m_keyboard;
	std::hash_map<int, bool> m_mouse;
	static std::unique_ptr<Keys> m_instance;
};
#endif