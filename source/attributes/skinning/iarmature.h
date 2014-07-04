#ifndef H_IARMATURE
#define H_IARMATURE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class vec3;
	class quat;
	class mat4;
}
namespace Core { class String; }
namespace Attributes {

	class Bone;
	class Action;
	class IArmatureSchema;

	DECLARE_PUNK_GUID(IID_IArmature, "A67EECF9-EC55-4830-93BA-3BDE1207B332");

	class IArmature : public Core::IObject {
	public:
		virtual const Math::vec3 GetBoneLocalPosition(std::uint32_t index) = 0;
		virtual const Math::vec3 GetBoneGlobalPosition(std::uint32_t index) = 0;
		virtual const Math::quat GetBoneLocalRotation(std::uint32_t index) = 0;
		virtual const Math::quat GetBoneGlobalRotation(std::uint32_t index) = 0;
		virtual const Math::mat4 GetBoneLocalMatrix(std::uint32_t index) = 0;
		virtual const Math::mat4 GetBoneGlobalMatrix(std::uint32_t index) = 0;
		virtual const Math::mat4 GetBoneGlobalRestMatrix(std::uint32_t index) = 0;
		virtual void SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) = 0;
		virtual void SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) = 0;
		virtual void SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) = 0;
		virtual void SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) = 0;
		virtual void SetSchemaName(const Core::String& name) = 0;
		virtual const Core::String& GetSchemaName() const = 0;
		virtual const Core::Pointer<IArmatureSchema> GetSchema() const = 0;
		virtual void SetSchema(Core::Pointer<IArmatureSchema> value) = 0;
		virtual void SetName(const Core::String& name) = 0;
		virtual const Core::String& GetName() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	H_IARMATURE