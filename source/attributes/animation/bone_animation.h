#ifndef _H_PUNK_VIRTUAL_BONE_ANIMATION
#define _H_PUNK_VIRTUAL_BONE_ANIMATION

#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class BoneAnimation : public Animation
	{
	public:
		BoneAnimation();
		virtual ~BoneAnimation();
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_BONE_ANIMATION
