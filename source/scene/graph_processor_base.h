#ifndef _H_GRAPH_PROCESSOR_BASE
#define _H_GRAPH_PROCESSOR_BASE

#include <system/concurrency/module.h>
#include "igraph_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class CommandBase;

	class PUNK_ENGINE_API GraphProcessorBase : public IGraphProcessor {
	public:		
		ISceneGraph* GetGraph() const override;
		void StartProcessing() override;
		void BeginUpdate(int dt_ms) override;
		void FinishUpdate() override;
		void WaitUpdateStart() override;
		void WaitUpdateFinish() override;
		void StopProcessing() override;
		void WaitProcessingComplete() override;
		void Destroy() override;
		bool IsFinish() const override;

		void PreUpdate();
		void PostUpdate();
		void InternalUpdate();
		void AddCommand(CommandBase* cmd);
		void AddInternalCommand(CommandBase* task);
	protected:
		virtual void OnStartProcessing() = 0;
		virtual void OnInternalUpdate(int dt) {}
		virtual void OnInternalUpdate(CommandBase* task) = 0;
		virtual void OnPreUpdate(CommandBase* command) = 0;
		virtual void OnPostUpdate(CommandBase* command) = 0;
		virtual void OnWaitProcessingComplete() = 0;

		void AssignGraph(ISceneGraph* graph);
	private:
		ISceneGraph* m_graph{ nullptr };
		System::ThreadMutex m_allow_update;
		System::Thread m_thread;
		int m_last_update_step{ 0 };

		System::ThreadMutex m_tasks_mutex;
		std::vector<CommandBase*> m_tasks;

		System::ThreadMutex m_commands_mutex;
		std::vector<CommandBase*> m_commands;
		bool m_delete{ false };
	};
}
PUNK_ENGINE_END

#endif	//	_H_GRAPH_PROCESSOR_BASE