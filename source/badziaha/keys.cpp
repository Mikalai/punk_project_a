#include "keys.h"
#include <hash_map>
#include <QtGui/qevent.h>

std::unique_ptr<Keys> Keys::m_instance;

Keys* Keys::instance() {
	if (!m_instance.get()) {
		m_instance.reset(new Keys);
	}
	return m_instance.get();
}

void Keys::destroy() {
	m_instance.reset(nullptr);
}

void Keys::setKeyboard(int key, bool state) {
	m_keyboard[key] = state;
}
bool Keys::keyboard(int key) {
	return m_keyboard[key];
}