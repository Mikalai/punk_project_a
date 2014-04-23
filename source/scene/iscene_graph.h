#ifndef ISCENE_GRAPH_H
#define ISCENE_GRAPH_H

#include <core/action.h>
#include <memory>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Scene {

    class INode;

    class ISceneGraph {
    public:
        virtual ~ISceneGraph() = 0;
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
        virtual INode* GetRoot() = 0;
        virtual const INode* GetRoot() const = 0;
        virtual void SetRoot(INode* node) = 0;
		virtual INode* ReleaseRoot() = 0;
        virtual void AddNodeAddedAction(Core::ActionBase<INode*, INode*>* value) = 0;
        virtual void AddNodeRemovedAction(Core::ActionBase<INode*, INode*>* value) = 0;
        virtual void OnNodeAdded(INode* parent, INode* child) = 0;
        virtual void OnNodeRemoved(INode* parent, INode* child) = 0;
    };

    inline ISceneGraph::~ISceneGraph() {}

    using ISceneGraphUniquePtr = std::unique_ptr<ISceneGraph, void (*)(ISceneGraph*)>;

    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& fullpath);
    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateScene();
    extern PUNK_ENGINE_API void DestroyScene(ISceneGraph* graph);
}
PUNK_ENGINE_END

#endif // ISCENE_GRAPH_H
