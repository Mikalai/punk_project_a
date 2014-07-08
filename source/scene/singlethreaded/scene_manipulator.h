#ifndef _H_ISCENE_MANIPULATOR
#define _H_ISCENE_MANIPULATOR

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace SceneModule {

	class INode;

	class ISceneManipulator : public Core::IObject {
	public:
		virtual void DestroyCurrentScene() = 0;
		virtual void LoadSceneFromFile(const Core::String& filename);
		virtual Core::Pointer<INode> GetNode(const Core::String& name);		
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISCENE_MANIPULATOR