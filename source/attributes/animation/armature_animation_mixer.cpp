#include <ostream>
#include <math.h>
#include <istream>
#include <system/environment.h>
#include <math/helper.h>
#include <math/matrix_helper.h>
#include <attributes/skinning/module.h>
#include <system/logger/module.h>
#include "armature_animation_mixer.h"
#include "bone_animation.h"
#include "action.h"


PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti ArmatureAnimationMixerType{ L"Attributes.ArmatureAnimationMixer"
		, typeid(ArmatureAnimationMixer).hash_code()
		, { AnimationMixer::Type() } };

	Core::Rtti* ArmatureAnimationMixer::Type() {
		return &ArmatureAnimationMixerType;
	}

    ArmatureAnimationMixer::ArmatureAnimationMixer()
        : m_current_time(0)
        , m_armature(nullptr)
    {}

    ArmatureAnimationMixer::~ArmatureAnimationMixer()
    {}

    bool ArmatureAnimationMixer::GetBoneMatrix(const Core::String& bone, Math::mat4& matrix)
    {
        try
        {
            Math::mat4 pos = Math::CreateTranslate(m_result[GetBoneIndex(bone)].m_position);
            Math::mat4 rot = Math::CreateFromQuaternion(m_result[GetBoneIndex(bone)].m_rotation);
            matrix = pos*rot;
            return true;
        }
        catch(std::out_of_range&)
        {
            System::GetDefaultLogger()->Error("No bone in armature with name " + bone);
            return false;
        }
        return true;
    }

    void ArmatureAnimationMixer::SetTrackTime(float frame)
    {
        size_t result_size = m_armature->GetBonesCount();
        m_result.resize(result_size);
        for (auto& bone : m_result)
        {
            bone.m_position.Set(0,0,0);
            bone.m_rotation.Set(0,0,0,0);
        }

        for (size_t track_index = 0; track_index != m_tracks_array.size(); ++track_index)
        {
            TrackOption& options = m_options[track_index];
            Action* action = m_tracks_array[track_index];
            m_current_time = frame;
            //	find correct time
            if (options.m_enable)
            {
                if (m_current_time  > action->GetEndFrame())
                {
                    if (options.m_loop)
                    {
                        if (action->GetEndFrame() > 0)
                            while (m_current_time  > action->GetEndFrame()) m_current_time  -= action->GetEndFrame();
                    }
                    else
                        m_current_time = action->GetEndFrame();
                }

                for (size_t bone_index = 0; bone_index != m_bones_animation_cache[track_index].size(); ++bone_index)
                {
                    const BoneAnimation* track = m_bones_animation_cache[track_index][bone_index];

                    Math::vec3 pos = track->GetPosition(m_current_time);
                    Math::quat rot = track->GetRotation(m_current_time);

                    m_result[bone_index].m_position += pos * options.m_weight;
                    m_result[bone_index].m_rotation += rot * options.m_weight;
                }
            }
        }

        UpdateGlobalMatrix();
    }

    void ArmatureAnimationMixer::EnableTrack(const Core::String& track_name, bool flag)
    {
        m_options[GetTrackIndex(track_name)].m_enable = flag;
    }

    void ArmatureAnimationMixer::DisableAllTracks()
    {
        for (auto& option : m_options)
        {
            option.m_enable = false;
        }
    }

    void ArmatureAnimationMixer::SetTrackWeight(const Core::String& track_name, float value)
    {
        m_options[GetTrackIndex(track_name)].m_weight = value;
    }

    void ArmatureAnimationMixer::SetLooping(const Core::String& track_name, bool flag)
    {
        m_options[GetTrackIndex(track_name)].m_loop = flag;
    }

    size_t ArmatureAnimationMixer::GetTrackIndex(const Core::String& value)
    {
        for (size_t i = 0; i != m_tracks.size(); ++i)
        {
            if (m_tracks[i] == value)
                return i;
        }
        return -1;
    }

    size_t ArmatureAnimationMixer::GetBoneIndex(const Core::String& value)
    {
        return m_armature->GetBoneIndex(value);
    }

    void ArmatureAnimationMixer::EnableTrack(size_t track, bool flag)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_enable = flag;
    }

    void ArmatureAnimationMixer::SetTrackWeight(size_t track, float value)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_weight = value;
    }

    void ArmatureAnimationMixer::SetLooping(size_t track, bool flag)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_loop = flag;
    }

    bool ArmatureAnimationMixer::GetBoneMatrix(size_t bone, Math::mat4& matrix)
    {
        Math::mat4 pos = Math::CreateTranslate(m_result[bone].m_position);
        Math::mat4 rot = Math::CreateFromQuaternion(m_result[bone].m_rotation);
        matrix = pos*rot;
        return true;
    }

    void ArmatureAnimationMixer::UpdateGlobalMatrix()
    {
        m_animated_global_matrix.resize(m_armature->GetBonesCount());
        for (size_t i = 0; i != m_armature->GetRootsBonesCount(); ++i)
        {
            UpdateBonesMatrix(m_armature->GetRootBone(i));
        }
    }

    void ArmatureAnimationMixer::UpdateBonesMatrix(Bone* value)
    {
        const Bone* parent = value->GetParent();
        if (parent)
        {
            Math::mat4 bone_matrix;
            GetBoneMatrix(value->GetIndex(), bone_matrix);
            Math::mat4 global = m_animated_global_matrix[parent->GetIndex()] * value->GetLocalMatrix() * bone_matrix * value->GetLocalMatrix().Inversed();
            m_animated_global_matrix[value->GetIndex()] = global;
        }
        else
        {
            Math::mat4 bone_matrix;
            GetBoneMatrix(value->GetIndex(), bone_matrix);
            Math::mat4 global = value->GetLocalMatrix() * bone_matrix * value->GetLocalMatrix().Inversed();
            m_animated_global_matrix[value->GetIndex()] = global;
        }
        for (auto child : value->GetChildren())
        {
            UpdateBonesMatrix(child);
        }
    }

    const Math::mat4& ArmatureAnimationMixer::GetAnimatedGlobalMatrix(size_t bone) const
    {
        return m_animated_global_matrix[bone];
    }

    Armature* ArmatureAnimationMixer::GetArmature()
    {
        return m_armature;
    }

    void ArmatureAnimationMixer::SetArmature(Armature *value)
    {
        m_armature = value;
        if (m_armature)
        {
            for (auto action_name : m_armature->GetSupportedActionArray())
            {
                Action* action = nullptr;//Cast<Action*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + action_name + Core::String(L".action")));
                m_tracks.push_back(action_name);
                m_options.push_back(TrackOption());
                m_tracks_array.push_back(action);
                size_t track_index = m_tracks.size() - 1;
                m_bones_animation_cache.push_back(std::vector<BoneAnimation*>());
                m_bones_animation_cache[track_index].resize(m_armature->GetBonesCount());
                for (auto o : *action)
                {
                    BoneAnimation* anim = As<BoneAnimation*>(o);
                    if (!anim)
                        continue;
                    m_bones_animation_cache[track_index][GetBoneIndex(anim->GetName())] = anim;
                }
            }
            DisableAllTracks();
            if (!m_options.empty())
                m_options[0].m_enable = true;
            SetTrackTime(0);
        }
    }    

//    void ArmatureAnimationMixer::AddBoneAnimation(const Core::String &track_name, const Core::String &bone_name, BoneAnimation *anim)
//    {
//        auto track_index = GetTrackIndex(track_name);
//        if (track_index == -1)
//        {
//            m_tracks.push_back(track_name);
//            track_index = m_tracks.size() - 1;
//            m_tracks_array.resize(m_armature.GetBonesCount());
//        }
//        m_tracks_array[track_index][GetBoneIndex(bone_name)] = anim;
//    }
}
PUNK_ENGINE_END
