#ifndef SHADER_UNIFORM_TABLE_H
#define SHADER_UNIFORM_TABLE_H

#include <array>
#include <config.h>
#include "shader_data_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	enum class ShaderUniformTable {
		WorldMatrix,
		ViewMatrix,
		ProjectionMatrix,
		ViewWorldMatrix,
		ProjectionViewWorldMatrix,
		NormalMatrix,
		LightProjectionMatrix,
		LightViewMatrix,
		LightPosition,
		LightPositionArray,
		LightDirection,
		LightDirectionArray,
		LightDiffuseColor,
		LightDiffuseColorArray,
		LightConstantAttenuation,
		LightConstantAttenuationArray,
		LightLinearAttenuation,
		LightLinearAttenuationArray,
		LightQuadricAttenuation,
		LightQuadricAttenuationArray,
		LightMode,
		LightModeArray,
		LightSpotExponent,
		LightSpotExponentArray,
		LightType,
		LightTypeArray,
		TextureMatrix,
		TextureMatrixArray,
		ShadowMapsArray,
		DiffuseMap0,
		DiffuseMap1,
		NormalMap,
		SpecularMap,
		DepthMap,
		TextureSize,
		DistanceVector, //  used for shadow mapping, stores distance of the frustum ???
		AmbientColor,
		SpecularColor,
		DiffuseColor,
		SpecularPower,
		NearDistance,
		FarDistance,
		FilterType,
		BonesArray,
		Time,
		TotalCount
	};

	constexpr int GetIndex(const ShaderUniformTable value) {
		return (int)value;
	}

	struct ShaderUniformNameMapping {
		ShaderUniformTable m_code;
		const char* m_name;
	};

	const std::array < ShaderUniformNameMapping, GetIndex(ShaderUniformTable::TotalCount) > ShaderUniformNameMap
	{
		{
			{ ShaderUniformTable::WorldMatrix, "uWorldMatrix" },
			{ ShaderUniformTable::ViewMatrix, "uViewMatrix" },
			{ ShaderUniformTable::ProjectionMatrix, "uProjectionMatrix" },
			{ ShaderUniformTable::ViewWorldMatrix, "uViewWorldMatrix" },
			{ ShaderUniformTable::ProjectionViewWorldMatrix, "uProjectionViewWorldMatrix" },
			{ ShaderUniformTable::NormalMatrix, "uNormalMatrix" },
			{ ShaderUniformTable::LightProjectionMatrix, "uLightProjectionMatrix" },
			{ ShaderUniformTable::LightViewMatrix, "uLightViewMatrix" },
			{ ShaderUniformTable::LightPosition, "uLightPosition" },
			{ ShaderUniformTable::LightPositionArray, "uLightPositionArray" },
			{ ShaderUniformTable::LightDirection, "uLightDirection" },
			{ ShaderUniformTable::LightDirectionArray, "uLightDirectionArray" },
			{ ShaderUniformTable::LightDiffuseColor, "uLightDiffuseColor" },
			{ ShaderUniformTable::LightDiffuseColorArray, "uLightDiffuseColorArray" },
			{ ShaderUniformTable::LightConstantAttenuation, "uLightConstantAttenuation" },
			{ ShaderUniformTable::LightConstantAttenuationArray, "uLightConstantAttenuationArray" },
			{ ShaderUniformTable::LightLinearAttenuation, "uLightLinearAttenuation" },
			{ ShaderUniformTable::LightLinearAttenuationArray, "uLightLinearAttenuationArray" },
			{ ShaderUniformTable::LightQuadricAttenuation, "uLightQuadricAttenuation" },
			{ ShaderUniformTable::LightQuadricAttenuationArray, "uLightQuadricAttenuationArray" },
			{ ShaderUniformTable::LightMode, "uLightMode" },
			{ ShaderUniformTable::LightModeArray, "uLightModeArray" },
			{ ShaderUniformTable::LightSpotExponent, "uLightSpotExponent" },
			{ ShaderUniformTable::LightSpotExponentArray, "uLightSpotExponentArray" },
			{ ShaderUniformTable::LightType, "uLightType" },
			{ ShaderUniformTable::LightTypeArray, "uLightTypeArray" },
			{ ShaderUniformTable::TextureMatrix, "uTextureMatrix" },
			{ ShaderUniformTable::TextureMatrixArray, "uTextureMatrixArray" },
			{ ShaderUniformTable::ShadowMapsArray, "uShadowMapsArray" },
			{ ShaderUniformTable::DiffuseMap0, "uDiffuseMap0" },
			{ ShaderUniformTable::DiffuseMap1, "uDiffuseMap1" },
			{ ShaderUniformTable::NormalMap, "uNormalMap" },
			{ ShaderUniformTable::SpecularMap, "uSpecularMap" },
			{ ShaderUniformTable::DepthMap, "uDepthMap" },
			{ ShaderUniformTable::TextureSize, "uTextureSize" },
			{ ShaderUniformTable::DistanceVector, "uDistanceVector" },
			{ ShaderUniformTable::AmbientColor, "uAmbientColor" },
			{ ShaderUniformTable::SpecularColor, "uSpecularColor" },
			{ ShaderUniformTable::DiffuseColor, "uDiffuseColor" },
			{ ShaderUniformTable::SpecularPower, "uSpecularPower" },
			{ ShaderUniformTable::NearDistance, "uNearDistance" },
			{ ShaderUniformTable::FarDistance, "uFarDistance" },
			{ ShaderUniformTable::FilterType, "uFilterType" },
			{ ShaderUniformTable::BonesArray, "uBonesArray" },
			{ ShaderUniformTable::Time, "uTime" },
		}
	};

	inline const char* GetUniformName(ShaderUniformTable value) {
		for (auto& i : ShaderUniformNameMap) {
			if (i.m_code == value)
				return i.m_name;
		}

		return "";
	}

	template<ShaderDataType ParameterType, ShaderUniformTable UniformParameter>
	struct ShaderUniformParameter {

		static const ShaderUniformTable Parameter = UniformParameter;
		static const ShaderDataType Type = ParameterType;

		static const std::string ToString() {
			std::stringstream stream;
			stream << "uniform " << GetDataTypeName(ParameterType) << " " << GetUniformName(Parameter) << ";\n";
			return stream.str();
		}
	};

	template<typename ... UniformParameters> struct ShaderUniformBlock;

	template<>
	struct ShaderUniformBlock<> {
		const std::string ToString() { return "\n"; }
	};

	template<typename UniformParameter, typename ... UniformParameters>
	struct ShaderUniformBlock<UniformParameter, UniformParameters...> : public ShaderUniformBlock<UniformParameters...>{
		const std::string ToString() {
			std::stringstream stream;
			stream << UniformParameter::ToString() << ShaderUniformBlock<UniformParameters...>::ToString();
			return stream.str();
		}
	};
}
PUNK_ENGINE_END

#endif // SHADER_UNIFORM_TABLE_H
