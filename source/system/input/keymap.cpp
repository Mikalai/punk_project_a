#include "system/errors/module.h"
#include "system/events/key_event.h"
#include "keymap.h"

PUNK_ENGINE_BEGIN
namespace System
{
	static Core::Rtti KeyMapType{ "Punk.Engine.System.KeyMap", typeid(KeyMap).hash_code(), { Core::Object::Type() } };

	Core::Rtti* KeyMap::Type(){
		return &KeyMapType;
	}

	struct KeyMapImpl
	{
		~KeyMapImpl()
		{}

		KeyboardActionsCollection m_actions;
	};

	void KeyMap::Add(Key key, KeyboardAction action)
	{
		impl->m_actions[key].insert(action);
	}

	void KeyMap::Remove(Key key, KeyboardAction action)
	{
		auto key_it = impl->m_actions.find(key);
		if (key_it == impl->m_actions.end())
			return;
		auto action_it = key_it->second.find(action);
		if (key_it->second.end() == action_it)
			return;
		key_it->second.erase(action_it);
	}

	std::set<KeyboardAction>& KeyMap::GetActions(Key key)
	{
		return impl->m_actions[key];
	}

	const std::set<KeyboardAction>& KeyMap::GetActions(Key key) const
	{
		auto it = impl->m_actions.find(key);
		if (it == impl->m_actions.end())
			throw Error::SystemException("Key was not found");
		return it->second;
	}

	void KeyMap::OnKeyEvent(const KeyEvent &event) {
		for (auto action : impl->m_actions[event.key]) {
			(*action)(event);
		}
	}

	KeyMap::KeyMap()
		: impl(new KeyMapImpl)
	{
	}

	KeyMap::~KeyMap()
	{
		delete impl;
		impl = nullptr;
	}
}
PUNK_ENGINE_END
