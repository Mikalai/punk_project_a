#ifndef _H_ISCENE_BUILDER
#define _H_ISCENE_BUILDER

#include <config.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
	class ISceneBuilder {
	public:
		virtual INode* CreateNode(INode* parent);
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISCENE_BUILDER