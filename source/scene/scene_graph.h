#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include <system/concurrency/thread_mutex.h>
#include "inode.h"
#include "iscene_graph.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    class PUNK_ENGINE_LOCAL SceneGraph : public ISceneGraph {
	public:
        virtual ~SceneGraph();
        void Lock() override;
        void Unlock() override;
        INode* GetRoot() override;
        const INode* GetRoot() const override;
        void SetRoot(INode* node) override;

    private:
        System::ThreadMutex m_lock;
        INode* m_root {nullptr};
	};

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
