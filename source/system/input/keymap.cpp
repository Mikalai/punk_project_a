#include "system/errors/module.h"
#include "system/events/key_event.h"
#include "keymap.h"

PUNK_ENGINE_BEGIN
namespace System
{
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

	void KeyMap::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IKeyMap });
	}

	std::uint32_t KeyMap::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t KeyMap::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}
}
PUNK_ENGINE_END
