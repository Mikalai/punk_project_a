#ifndef _H_VALUE_MONITOR
#define _H_VALUE_MONITOR

#include "action.h"

PUNK_ENGINE_BEGIN
namespace Core {

	template<class T>
	class ValueMonitor {
	public:
		ValueMonitor() {}

		explicit ValueMonitor(const T& value)
			: m_value{ value } {}

		void SetSilent(const T& value) {
			m_value = value;
		}

		operator const T& () {
			return m_value;
		}

		void Set(const T& value) {
			if (m_value != value) {
				auto old = m_value;
				m_value = value;
				m_on_value_changed_with_old(old, m_value);
				m_on_value_changed(m_value);
			}
		}

		const T& Get() const {
			return m_value;
		}

		void SubscribeOnValueChanged(Core::Pointer<ActionBase<const T&, const T&>> action) {
			m_on_value_changed_with_old.Add(action);
		}

		void UnsubscribeOnValueChanged(Core::Pointer<ActionBase<const T&, const T&>> action) {
			m_on_value_changed_with_old.Remove(action);
		}

		void SubscribeOnValueChanged(Core::Pointer<ActionBase<const T&>> action) {
			m_on_value_changed.Add(action);
		}

		void UnsubscribeOnValueChanged(Core::Pointer<ActionBase<const T&>> action) {
			m_on_value_changed.Remove(action);
		}

		void UnsubscribeOnValueChanged(void* o) {
			m_on_value_changed.RemoveOwnerActions(o);
			m_on_value_changed_with_old.RemoveOwnerActions(o);
		}

	private:
		T m_value;
		ActionSlot<const T&, const T&> m_on_value_changed_with_old;
		ActionSlot<const T&> m_on_value_changed;
	};
}
PUNK_ENGINE_END

#endif	//	_H_VALUE_MONITOR