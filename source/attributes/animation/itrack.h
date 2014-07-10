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

	DECLARE_PUNK_GUID(CLSID_Vec3Track, "70A0AAF1-7D80-45CF-8EB2-DE751FF4847C");
	DECLARE_PUNK_GUID(CLSID_Vec4Track, "EC2BFD0F-C342-4EEA-B9FF-04041440F4A5");
	DECLARE_PUNK_GUID(CLSID_Mat4Track, "2520B4EC-21E9-42ED-966D-FEE2AD6AC644");
	DECLARE_PUNK_GUID(CLSID_QuatTrack, "1936DC6D-C038-459A-8928-EA994C40EEA3");
	DECLARE_PUNK_GUID(CLSID_FloatTrack, "92F5193F-B260-49F8-BA23-854A313403C3");

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

		void Add(KeyFrame<T>* value) {
			AddKeyFrame((IKeyFrame*)value);
		}		
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITRACK