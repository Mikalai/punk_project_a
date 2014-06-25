//#include <system/factory/module.h>
//#include <system/concurrency/work_item.h>
//#include "inode.h"
//#include "iscene.h"
//#include "command.h"
//#include "scene_worker.h"
//#include "iscene_processor.h"
//
//PUNK_ENGINE_BEGIN
//namespace SceneModule {
//
//	class LoaderWorkItem : public System::WorkItem {
//	public:
//		void Run(void *data) override {
//			ISceneWorker* worker = (ISceneWorker*)data;
//			if (!worker)
//				return;
//			
//			while (!worker->IsFinish()) {
//				
//				worker->WaitProcessStart();
//
//				worker->PreProcess();
//				worker->Process();
//				worker->PostProcess();
//
//				worker->IndicateProcessComplete();
//			}
//		}
//	};
//
//	SceneWorker::SceneWorker() {
//	}
//
//	SceneWorker::~SceneWorker() {
//		if (m_processor) {
//			m_processor->Terminate();
//			m_processor->Release();
//			m_processor = nullptr;
//		}
//	}
//	
//	void SceneWorker::WaitProcessStart() {
//		m_process_mutex.Lock();		
//	}
//
//	void SceneWorker::IndicateProcessComplete() {
//		m_process_mutex.Unlock();
//	}
//
//	void SceneWorker::WaitProcessComplete() {
//		m_process_mutex.Lock();
//	}
//
//	void SceneWorker::IndicateProcessStart() {
//		m_process_mutex.Unlock();
//	}
//
//	void SceneWorker::PreProcess() {
//		if (m_processor) {
//			m_processor->BeginPreProcessSync();
//			m_processor->PreProcess();
//			m_processor->EndPreProcessSync();
//		}		
//	}
//
//	void SceneWorker::Process() {
//		if (m_processor) {
//			m_processor->InternalProcess();
//		}
//	}
//
//	void SceneWorker::PostProcess() {
//		if (m_processor) {
//			m_processor->BeginPostProcessSync();
//			m_processor->PreProcess();
//			m_processor->EndPostProcessSync();
//		}
//	}
//
//	bool SceneWorker::IsFinish() const {
//		if (m_processor) {
//			if (m_delete) {
//				m_processor->WaitComplete();
//				return true;
//			}
//		}
//		return m_delete;
//	}	
//
//	void SceneWorker::Start() {
//		m_thread.Start(new LoaderWorkItem, this);
//		m_thread.Resume();
//	}
//
//	void SceneWorker::Stop() {
//		m_delete = true;
//		m_thread.Join();		
//	}
//
//	void SceneWorker::SetProcessor(ISceneProcessor* value) {
//		if (m_processor) {
//			m_processor->Terminate();
//			m_processor->Release();
//		}
//		value->AddRef();
//		m_processor = value;		
//	}
//
//	ISceneProcessor* SceneWorker::GetProcessor() const {
//		return m_processor;
//	}
//
//
//	void SceneWorker::QueryInterface(const Core::Guid& type, void** object) {
//		if (!object)
//			return;
//
//		if (type == Core::IID_IObject ||
//			type == IID_ISceneWorker) {
//			*object = (void*)this;
//			AddRef();
//		}
//		else
//			*object = nullptr;
//	}
//
//	void CreateSceneWorker(void** object) {
//		if (!object)
//			return;
//		*object = (void*)(new SceneWorker);
//	}
//
//	PUNK_REGISTER_CREATOR(IID_ISceneWorker, CreateSceneWorker);
//}
//PUNK_ENGINE_END
