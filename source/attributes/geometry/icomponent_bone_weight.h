#ifndef _H_ICOMPONENT_BONE_WEIGHT
#define _H_ICOMPONENT_BONE_WEIGHT

#include <config.h>
#include <cstdint>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Attributes {
	class IBoneWeightComponent {
	public:
		//virtual std::uint32_t GetInfluencingBonesCount(std::uint32_t vertex_index) = 0;
		virtual const Math::vec4* GetVertexBoneWeights(std::uint32_t index) const = 0;
		virtual const Math::ivec4* GetVertexBonesIndecies(std::uint32_t index) const = 0;
		virtual void SetVertexBoneWeight(std::uint32_t vertex_index, const Core::String& bone, float weight);
		virtual void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) = 0;
		virtual void SetVertexBonesWeights(const Math::vec4v& weights, const Math::ivec4v& bones) = 0;
		virtual bool HasVertexBoneWeights() const = 0;
		virtual const Core::String& GetArmatureSchema() const = 0;
		virtual void SetArmatureSchema(Core::String& value) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_BONE_WEIGHT
