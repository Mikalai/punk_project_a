#ifndef _H_ITRACK
#define _H_ITRACK

#include <config.h>
#include <core/iobject.h>
#include "ikeyframe.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ITrack, "AB556E27-C9A2-4F6F-9FC0-797FE020665A");
	DECLARE_PUNK_GUID(IID_IVec3Track, "EA009DC0-B8F6-468C-9ED7-EA2125902EBE");
	DECLARE_PUNK_GUID(IID_IVec4Track, "FCEC27E6-0485-461D-8750-B17BC640942A");
	DECLARE_PUNK_GUID(IID_IMat4Track, "FD05E315-21BB-4A82-8FBD-ACE3257E8A74");
	DECLARE_PUNK_GUID(IID_IQuatTrack, "0D968AF8-DDC6-4FD0-954A-287F4E329941");
	DECLARE_PUNK_GUID(IID_IFloatTrack, "72E39F12-59AA-41EC-B598-E184FCF00A08");

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
		virtual std::uint32_t GetKeySize() const = 0;
	};

	template<class T>
	class Track : public ITrack {
	public:

		KeyFrame<T>* KeyBefore(std::int32_t frame) {
			return (KeyFrame<T>*)GetKeyBefore(frame);
		}

		KeyFrame<T>* KeyAfter(std::int32_t frame) {
			return (KeyFrame<T>*)GetKeyAfter(frame);
		}

		void AddKeyFrame(KeyFrame<T>* value) {
			ITrack::AddKeyFrame(value);
		}		
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITRACK