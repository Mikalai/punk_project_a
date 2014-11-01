#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <system/logger/module.h>
#include "iimpulse_generator.h"

PUNK_ENGINE_BEGIN
namespace System {

	class ImpulseGenerator : public IImpulseGenerator {
	public:

		ImpulseGenerator() {
			m_thread = std::thread(ImpulseGeneratorThread, this);
		}

		virtual ~ImpulseGenerator() {
			Terminate();
		}

		static void ImpulseGeneratorThread(ImpulseGenerator* generator) {
			generator->Update();
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;

			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = this;
				AddRef();
			}
			else if (type == IID_IImpulseGenerator) {
				*object = (IImpulseGenerator*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IImpulseGenerator
		struct Record {
			std::uint32_t multiplier{ 1 };
			std::uint32_t current{ 0 };
			ImpulsedAction action;

			Record(std::uint32_t m, ImpulsedAction a)
				: multiplier{ m }
				, current{ m }
				, action{ a }
			{}
		};

		void SetPeriod(std::uint32_t milliseconds) override {

		}

		std::uint32_t GetPeriod() override {
			return 0;
		}

		void AddAction(std::uint32_t multiplier, ImpulsedAction action, bool repeat) override {
			std::lock_guard<std::recursive_mutex> lock(m_mutex);
			RemoveAction(action);
			Record r{ multiplier, action };
			m_actions.push_back(r);
		}

		void RemoveAction(ImpulsedAction action) override {
			std::lock_guard<std::recursive_mutex> lock(m_mutex);
			auto it = std::find_if(m_actions.begin(), m_actions.end(), [&action](const Record& r) {
				return r.action == action;
			});
			if (it == m_actions.end())
				return;
			m_actions.erase(it);
		}

		void Update() {
			LOG_SCOPE("Impulse generator thread...");
			auto p1 = std::chrono::system_clock::now();
			auto p2 = p1;

			while (!m_terminate) {
				auto p1 = std::chrono::high_resolution_clock::now();
				auto diff = p1 - p2;
				auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
				//std::cout << microseconds << std::endl;
				if (m_current < microseconds) {
					std::cout << "Trigger actions..." << std::endl;
					std::lock_guard<std::recursive_mutex> lock(m_mutex);
					for (auto& r : m_actions) {
						if (r.current == 0) {
							r.current = r.multiplier;
							r.action->operator()((r.current + 1) * m_period);
						}
						else {
							r.current--;
						}
					}
					m_current = m_period;
				}
				else {
					m_current -= microseconds;
					//std::cout << "Left " << m_current << std::endl;
				}
				p2 = p1;
			}
		}

		void Terminate() {
			m_terminate = true;
			m_thread.join();
		}
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		bool m_terminate{ false };
		std::thread m_thread;
		std::vector<Record> m_actions;
		std::recursive_mutex m_mutex;
		std::uint64_t m_current{ 1000000 };
		std::uint64_t m_period{ 1000000 };	//	1s
	};

	std::mutex g_generator_mutex;
	static ImpulseGenerator* g_generator = nullptr;

	extern "C" PUNK_ENGINE_API IImpulseGenerator* GetImpulseGeneratorInstance() {
		std::lock_guard<std::mutex> lock(g_generator_mutex);
		if (g_generator == nullptr) {
			g_generator = new ImpulseGenerator;
			g_generator->AddRef();
		}
		return g_generator;
	}

	extern "C" PUNK_ENGINE_API void DestroyImpulseGeneratorInstance() {
		std::lock_guard<std::mutex> lock(g_generator_mutex);
		if (!g_generator->Release())
			g_generator = nullptr;
	}
}
PUNK_ENGINE_END