//#ifndef _H_SCENE_WORKER
//#define _H_SCENE_WORKER
//
//#include <system/concurrency/module.h>
//#include "iscene_worker.h"
//
//PUNK_ENGINE_BEGIN
//namespace SceneModule {
//	
//	class CommandBase;
//
//	class PUNK_ENGINE_LOCAL SceneWorker : public ISceneWorker {
//	public:		
//		SceneWorker();
//		virtual ~SceneWorker();
//		
//		void QueryInterface(const Core::Guid& type, void** object) override;
//
//		void SetProcessor(ISceneProcessor* value) override;
//		ISceneProcessor* GetProcessor() const override;
//		void Start() override;
//		void Stop() override;
//		bool IsFinish() const override;
//		void IndicateProcessStart() override;
//		void WaitProcessStart() override;
//		void PreProcess() override;
//		void Process() override;
//		void PostProcess() override;
//		void IndicateProcessComplete() override;
//		void WaitProcessComplete() override;
//
//	private:
//		System::ThreadMutex m_process_mutex;
//		ISceneProcessor* m_processor{ nullptr };				
//		mutable System::Thread m_thread;
//		bool m_delete { false };
//		PUNK_OBJECT_DEFAULT_IMPL3(SceneWorker);
//	};
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_GRAPH_PROCESSOR_BASE