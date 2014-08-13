#include <set>
#include <system/concurrency/module.h>
#include "idebugger.h"

PUNK_ENGINE_BEGIN
namespace System {

	class Debugger : public IDebugger {
	public:
		void TrackInstance(ISupportDebug* instance) override {
			m_instances.insert(instance);
		}

		void UntrackInstance(ISupportDebug* instance) override {
			m_instances.erase(instance);
		}

		std::uint32_t GetTrackInstanceCount() const override {
			return (std::uint32_t)m_instances.size();
		}

		ISupportDebug* FirstTrackInstance() const override {			
			m_it = m_instances.begin();
			if (m_it != m_instances.end())
				return *m_it;
			return nullptr;
		}

		ISupportDebug* NextTrackInstance() const override {
			++m_it;
			if (m_it != m_instances.end())
				return *m_it;
			return nullptr;
		}

		void Lock() override {
			m_mutex.Lock();
		}

		void Unlock() override {
			m_mutex.Unlock();
		}

	private:
		ThreadMutex m_mutex;
		std::set < ISupportDebug* > m_instances;
		mutable std::set < ISupportDebug* >::iterator m_it;
	};

	ThreadMutex g_debugger_mutex;
	Debugger* g_debugger;

	extern "C" PUNK_ENGINE_API IDebugger* pesGetDebuggerInstance() {
		ThreadMutexLock lock(g_debugger_mutex);
		if (!g_debugger) {
			g_debugger = new Debugger;
		}
		return g_debugger;
	}

	extern "C" PUNK_ENGINE_API void pesDestroyDebuggerInstance() {
		ThreadMutexLock lock(g_debugger_mutex);
		delete g_debugger;
		g_debugger = nullptr;
	}
}
PUNK_ENGINE_END
