#ifndef H_SHADER_ATTRIBUTE
#define H_SHADER_ATTRIBUTE

#include <array>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	enum class ShaderAttributeTable {
		VertexPosition,
		VertexNormal,
		VertexColor,
		VertexTangent,
		VertexBitangent,
		VertexTexture0,
		VertexTexture1,
		VertexTexture2,
		VertexTexture3,
		VertexBonesIndecies,
		VertexBonesWeights,
		VertexFlags
	};

	constexpr int GetIndex(const ShaderAttributeTable value) {
		return (int)value;
	}

	struct ShaderAttributeNameMapping {
		ShaderAttributeTable m_code;
		const char* m_name;
	};

	const std::array < ShaderAttributeNameMapping, int(ShaderDataType::TotalCount) > ShaderAttributeMap
	{
		{
			{ ShaderAttributeTable::VertexPosition, "VertexPosition" },
			{ ShaderAttributeTable::VertexNormal, "VertexNormal" },
			{ ShaderAttributeTable::VertexColor, "VertexColor" },
			{ ShaderAttributeTable::VertexTangent, "VertexTangent" },
			{ ShaderAttributeTable::VertexBitangent, "VertexBitangent" },
			{ ShaderAttributeTable::VertexTexture0, "VertexTexture0" },
			{ ShaderAttributeTable::VertexTexture1, "VertexTexture1" },
			{ ShaderAttributeTable::VertexTexture2, "VertexTexture2" },
			{ ShaderAttributeTable::VertexTexture3, "VertexTexture3" },
			{ ShaderAttributeTable::VertexBonesIndecies, "VertexBonesIndecies" },
			{ ShaderAttributeTable::VertexBonesWeights, "VertexBonesWeights" },
			{ ShaderAttributeTable::VertexFlags, "VertexFlags" }
		}
	};

	inline const char* GetShaderAttributeName(ShaderAttributeTable value) {
		for (auto& i : ShaderAttributeMap) {
			if (i.m_code == value)
				return i.m_name;
		}
		return "";
	}

	template<ShaderDataType ParameterType, ShaderAttributeTable AttributeParameter, int Layout>
	struct ShaderAttribute {

		static const int LayOut = Layout;
		static const ShaderAttributeTable Parameter = AttributeParameter;
		static const ShaderDataType Type = ParameterType;

		static const std::string ToString() {
			std::stringstream stream;
			stream << "layout (location=" << LayOut << ") in " << GetDataTypeName(ParameterType) << " " << GetShaderAttributeName(Parameter) << ";\n";
			return stream.str();
		}
	};

	template<typename ... AttributeParameters> struct ShaderVertexAttributesBlock;

	template<>
	struct ShaderVertexAttributesBlock < > {
		const std::string ToString() { return "\n"; }
	};

	template<typename AttributeParameter, typename ... AttributeParameters>
	struct ShaderVertexAttributesBlock<AttributeParameter, AttributeParameters...> : public ShaderVertexAttributesBlock < AttributeParameters... > {
		const std::string ToString() {
			std::stringstream stream;
			stream << AttributeParameter::ToString() << ShaderVertexAttributesBlock<AttributeParameters...>::ToString();
			return stream.str();
		}
	};
}
PUNK_ENGINE_END

#endif // SHADER_ATTRIBUTE
