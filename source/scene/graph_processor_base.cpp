#include "graph_processor_base.h"
#include "inode.h"
#include "iscene_graph.h"

PUNK_ENGINE_BEGIN
namespace Scene {

	class LoaderWorkItem : public System::WorkItem {
	public:
		void Run(void *data) override {
			GraphProcessorBase* proc = (GraphProcessorBase*)data;
			if (!proc)
				return;

			Scene::ISceneGraph* scene = proc->GetGraph();
			while (!proc->IsFinish()) {
				proc->WaitUpdateStart();

				bool process_scene = (scene = proc->GetGraph()) != nullptr;

				if (process_scene) {
					scene->Lock();
					proc->PreUpdate();
					scene->Unlock();
				}


				proc->InternalUpdate();

				if (process_scene) {
					scene->Lock();
					proc->PostUpdate();
					scene->Unlock();
				}

				proc->FinishUpdate();
			}
		}
	};

	GraphProcessorBase::GraphProcessorBase() {
		m_allow_update.Lock();
	}

	Scene::ISceneGraph* GraphProcessorBase::GetGraph() const {
		return m_graph;
	}

	void GraphProcessorBase::StartProcessing() {
		OnStartProcessing();
		m_thread.Start(new LoaderWorkItem, this);
		m_thread.Resume();
	}

	void GraphProcessorBase::InternalUpdate() {
		OnInternalUpdate(m_last_update_step);
		m_tasks_mutex.Lock();
		auto tasks = m_tasks;
		m_tasks.clear();
		m_tasks_mutex.Unlock();

		for (CommandBase* task : tasks) {
			OnInternalUpdate(task);			
			delete task;
		}
	}

	void GraphProcessorBase::PreUpdate() {
		std::stack<Scene::INode*> stack;
		stack.push(m_graph->GetRoot());

		while (!stack.empty()) {
			Scene::INode* node = stack.top();
			stack.pop();
			for (std::uint64_t i = 0; i < node->GetChildrenCount(); ++i)
				stack.push(node->GetChild(i));
		}
	}

	void GraphProcessorBase::PostUpdate() {
		m_commands_mutex.Lock();
		auto commands = m_commands;
		m_commands.clear();
		m_commands_mutex.Unlock();

		for (CommandBase* cmd : commands) {
			OnPostUpdate(cmd);
			delete cmd;			
		}
	}

	void GraphProcessorBase::WaitUpdateStart() {
		m_allow_update.Lock();
	}

	void GraphProcessorBase::WaitUpdateFinish() {
		m_allow_update.Lock();
	}

	void GraphProcessorBase::FinishUpdate() {
		m_allow_update.Unlock();
	}

	void GraphProcessorBase::BeginUpdate(int dt_ms) {
		m_last_update_step = dt_ms;
		m_allow_update.Unlock();
	}

	void GraphProcessorBase::AddCommand(CommandBase* cmd) {
		m_commands_mutex.Lock();
		m_commands.push_back(cmd);
		m_commands_mutex.Unlock();
	}

	void GraphProcessorBase::AddInternalCommand(CommandBase* task) {
		m_tasks_mutex.Lock();
		m_tasks.push_back(task);
		m_tasks_mutex.Unlock();
	}

	void GraphProcessorBase::AssignGraph(ISceneGraph* graph) {
		m_graph = graph;
	}

	bool GraphProcessorBase::IsFinish() const {
		return m_delete;
	}

	void GraphProcessorBase::WaitProcessingComplete() {
		bool need_lock = m_graph != nullptr;

		if (need_lock)
		{
			m_graph->Lock();
			OnWaitProcessingComplete();			
			m_graph->Unlock();
		}
		m_thread.Join();
	}

	void GraphProcessorBase::StopProcessing() {
		m_delete = true;
	}

	void GraphProcessorBase::Destroy() {}
}
PUNK_ENGINE_END
