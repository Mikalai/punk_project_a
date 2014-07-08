#ifndef KEYMAP_H
#define KEYMAP_H

#include <set>
#include <map>
#include <array>
#include "core/action.h"
#include "ikeymap.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class KeyEvent;

    struct KeyMapImpl;

    class PUNK_ENGINE_LOCAL KeyMap final : public IKeyMap
    {
    public:
        KeyMap();
        virtual ~KeyMap();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IKeyMap
        void OnKeyEvent(const KeyEvent& event) override;
        void Add(Key key, KeyboardAction action) override;
        void Remove(Key key, KeyboardAction action) override;
        std::set<KeyboardAction>& GetActions(Key key) override;
        const std::set<KeyboardAction>& GetActions(Key key) const override;
        
        KeyMapImpl* impl;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
    };
}
PUNK_ENGINE_END

#endif // KEYMAP_H
