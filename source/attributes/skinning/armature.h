#ifndef _H_PUNK_VIRTUAL_ARMATURE
#define _H_PUNK_VIRTUAL_ARMATURE

#include <memory>
#include <vector>

#include <config.h>
#include <core/object.h>
#include <string/string.h>
#include "bone.h"
#include "types.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
    class PUNK_ENGINE_API Armature : public Core::Object
	{
	public:
        typedef std::vector<Core::String> Actions;
        typedef std::vector<Bone*> Bones;
    public:
		Armature();
        Armature(const Armature&) = delete;
        Armature& operator = (const Armature&) = delete;
        virtual ~Armature();

		void AddRootBone(Bone* bone);
		int GetBoneIndex(const Core::String& name) const;
		Bone* GetBoneByName(const Core::String& name);
		const Bone* GetBoneByName(const Core::String& name) const;
		Bone* GetBoneByIndex(int index);
		const Bone* GetBoneByIndex(int index) const;		
		int GetRootsBonesCount() const { return m_root_bones.size(); }
		Bone* GetRootBone(int index) { return m_root_bones[index]; }
        const Bone* GetRootBone(int index) const { return m_root_bones[index]; }
		int GetBonesCount() const;

        void AddActionName(const Core::String& value);
        bool IsActionSupported(const Core::String& value);
        const Actions& GetSupportedActionArray() const;

        void SetName(const Core::String& value);
        const Core::String& GetName() const;

        void PrintDebug(Bone* parent, int level = 0);

		virtual void UpdateHierarchy();

        void CacheBones(Bone* b);
        void Clear();
	private:		

	private:
        Bones m_root_bones;
		BonesCache m_cache;
		BonesNamedCache m_named_cache;
        Actions m_supported_actions;
        Core::String m_name;

        PUNK_OBJECT(Armature)               
	};
}
PUNK_ENGINE_END

//REGISTER_MANAGER(L"resource.armatures", L"*.armature", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE, Attributes, Armature, return, return);

#endif	//	_H_PUNK_VIRTUAL_ARMATURE
