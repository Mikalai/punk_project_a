#ifndef _H_ITRACK
#define _H_ITRACK

#include <config.h>
#include <core/iobject.h>
#include "ikeyframe.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ITrack, "AB556E27-C9A2-4F6F-9FC0-797FE020665A");

	class ITrack : public Core::IObject {
	public:
		virtual std::uint32_t GetDuration() const = 0;
		virtual std::int32_t GetFirstFrame() const = 0;
		virtual std::int32_t GetLastFrame() const = 0;
		virtual void SetFirstFrame(std::int32_t value) = 0;
		virtual void SetLastFrame(std::int32_t value) = 0;
		virtual IKeyFrame* GetKeyBefore(std::int32_t frame) = 0;
		virtual IKeyFrame* GetKeyAfter(std::int32_t frame) = 0;
		virtual void AddKeyFrame(IKeyFrame* value) = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetName(const Core::String& value) = 0;
	};

	template<class T>
	class Track : public ITrack {
	public:

		KeyFrame<T>* GetKeyBefore(std::int32_t frame) override {
			return (KeyFrame<T>*)ITrack::GetKeyBefore(frame);
		}

		KeyFrame<T>* GetKeyAfter(std::int32_t frame) override {
			return (KeyFrame<T>*)ITrack::GetKeyAfter(frame);
		}

		void AddKeyFrame(KeyFrame<T>* value) {
			ITrack::AddKeyFrame(value);
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITRACK