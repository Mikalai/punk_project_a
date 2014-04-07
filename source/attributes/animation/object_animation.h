#ifndef _H_PUNK_VIRTUAL_OBJECT_ANIMATION
#define _H_PUNK_VIRTUAL_OBJECT_ANIMATION

#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class ObjectAnimation : public Animation
	{
	public:
		virtual ~ObjectAnimation();
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_OBJECT_ANIMATION
