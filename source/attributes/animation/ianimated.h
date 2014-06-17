#ifndef _H_ANIMATED
#define _H_ANIMATED

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAnimated, "9715B2A4-8C5F-4BC0-8B13-C0BC394AD179");

	class IAnimation;

	class IAnimated : public Core::IObject {
	public:
		virtual void SetAnimationData(IAnimation* value) = 0;
		virtual IAnimation* GetAnimationData() = 0;
		virtual void AddAnimation(const Core::String& name) = 0;
		virtual std::uint32_t GetAnimationsCount() const = 0;
		virtual const Core::String& GetAnimation(std::uint32_t index) const = 0;		
		virtual void Advance(std::int32_t track_index, std::int32_t frame, void* data, std::int32_t value) = 0;

	};
}
PUNK_ENGINE_END

#endif	//	H_ANIMATED