#ifndef _H_ICOMPONENT_BONE_WEIGHT
#define _H_ICOMPONENT_BONE_WEIGHT

#include <vector>
#include <utility>
#include <config.h>
#include <cstdint>
#include <math/vec4.h>
#include <math/mat4.h>

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
		virtual void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) = 0;
		virtual void SetVertexBonesWeights(const std::vector<std::vector<std::pair<int, float>>>& b) = 0;
		virtual bool HasVertexBoneWeights() const = 0;
		virtual const Core::String& GetArmatureSchema() const = 0;
		virtual void SetArmatureSchema(Core::String& value) = 0;
		virtual void SetArmatureOffset(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetArmatureOffset() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_BONE_WEIGHT
