#ifndef _H_IANIMATION
#define _H_IANIMATION

#include <config.h>
#include <core/iobject.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "itrack.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAnimation, "3B79F2D8-3FCA-4EDC-8DE2-F51B1E4BFA84");

	class IAnimation : public Core::IObject {
	public:
		virtual std::uint32_t GetDuration() const = 0;
		virtual std::int32_t GetFirstFrame() const = 0;
		virtual std::int32_t GetLastFrame() const = 0;
		virtual void AddTrack(ITrack* value) = 0;
		virtual std::uint32_t GetTracksCount() const = 0;
		virtual const ITrack* GetTrack(std::uint32_t index) const = 0;
		virtual ITrack* GetTrack(std::uint32_t index) = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;		
	};
}

PUNK_ENGINE_END

#endif	//	_H_IANIMATION