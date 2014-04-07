#include <attributes/skinning/module.h>
#include "parse_simple.h"
#include "parse_bone.h"
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{

    /// Parse single armature
    bool ParseArmature(Core::Buffer& buffer, Attributes::Armature* armature)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
            {
                throw Error::LoaderException("Can't parse object");
                return false;
            }

            Core::String word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                armature->UpdateHierarchy();
                return true;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                armature->SetName(name);
            }
                break;
            case WORD_ACTION_REF:
            {
                Core::String action;
                ParseBlockedString(buffer, action);
                armature->AddActionName(action);
            }
                break;
            case WORD_BONE:
            {
                std::unique_ptr<Attributes::Bone> bone(new Attributes::Bone);
                ParseBone(buffer, bone.get());
                Attributes::Bone* parent = armature->GetBoneByName(bone->GetParentName());
                if (parent)
                    parent->AddChild(bone.release());
                else
                    armature->AddRootBone(bone.release());
            }
                break;
            default:
                throw Error::LoaderException(L"Unknown keyword: " + word);
            }
        }
        return false;
    }

    bool ParseArmatures(Core::Buffer& buffer)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_ARMATURE:
            {
                std::unique_ptr<Attributes::Armature> armature(new Attributes::Armature);
                ParseArmature(buffer, armature.get());                
                armature.release();
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
PUNK_ENGINE_END
