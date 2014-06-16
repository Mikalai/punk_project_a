#ifndef _H_IANIMATION
#define _H_IANIMATION

#include <config.h>
#include <core/iobject.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "animation_track.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAnimation, "3B79F2D8-3FCA-4EDC-8DE2-F51B1E4BFA84");

	class IKeyFrame;

	class IAnimation : public Core::IObject {
	public:
		virtual void SetDuration(std::uint32_t value) = 0;
		virtual std::uint32_t GetDuration() const = 0;
		virtual std::int32_t GetFirstFrame() const;
		virtual std::int32_t GetLastFrame() const;
		virtual IKeyFrame* GetKeyBefore(std::int32_t frame) = 0;
		virtual IKeyFrame* GetKeyAfter(std::int32_t frame) = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetName(const Core::String& value) = 0;
	};
}

PUNK_ENGINE_END

#endif	//	_H_IANIMATION