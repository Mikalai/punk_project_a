#ifndef _H_ICOMPONENT_BONE_WEIGHT
#define _H_ICOMPONENT_BONE_WEIGHT

#include <config.h>
#include <cstdint>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class IArmatureSchema;
	class IBoneWeightComponent {
	public:
		virtual const Math::vec4* GetWeights(std::uint32_t index) const = 0;
		virtual const Math::ivec4* GetBonesIndex(std::uint32_t index) const = 0;
		virtual void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) = 0;
		virtual void SetVertexBonesWeights(const Math::vec4v& weights, const Math::ivec4v& bones) = 0;
		virtual bool HasVertexBoneWeights() const = 0;
		virtual const IArmatureSchema* GetArmatureSchema() const = 0;
		virtual void SetArmatureSchema(IArmatureSchema* value) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_BONE_WEIGHT
