#ifndef SHADER_VARIABLE_H
#define SHADER_VARIABLE_H

#include <array>
#include <config.h>
#include "shader_data_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	enum class ShaderVariableTable {
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
		VertexFlags,
		FragmentColor,
		VertexWorldPosition,
		VertexViewWorldPosition,
		VertexProjectionViewWorldPosition,
		VertexWorldNormal,
		VertexViewWorldNormal,
		VertexTextureCoordinate0,
		VertexTextureCoordinate1,
		VertexTextureCoordinate2,
		VertexTextureCoordinate3,
		ViewDirection,
		LightDirection,
		LightPosition,
		DiffuseColor,
		TotalCount
	};

	constexpr int GetIndex(const ShaderVariableTable value) {
		return (int)value;
	}

	struct ShaderVariableNameMapping {
		ShaderVariableTable m_code;
		const char* m_name;
	};

	const std::array < ShaderVariableNameMapping, GetIndex(ShaderVariableTable::TotalCount) > ShaderVariableNameMap
	{
		{
			{ ShaderVariableTable::VertexPosition, "VertexPosition" },
			{ ShaderVariableTable::VertexNormal, "VertexNormal" },
			{ ShaderVariableTable::VertexColor, "VertexColor" },
			{ ShaderVariableTable::VertexTangent, "VertexTangent" },
			{ ShaderVariableTable::VertexBitangent, "VertexBitangent" },
			{ ShaderVariableTable::VertexTexture0, "VertexTexture0" },
			{ ShaderVariableTable::VertexTexture1, "VertexTexture1" },
			{ ShaderVariableTable::VertexTexture2, "VertexTexture2" },
			{ ShaderVariableTable::VertexTexture3, "VertexTexture3" },
			{ ShaderVariableTable::VertexBonesIndecies, "VertexBonesIndecies" },
			{ ShaderVariableTable::VertexBonesWeights, "VertexBonesWeights" },
			{ ShaderVariableTable::VertexFlags, "VertexFlags" },
			{ ShaderVariableTable::FragmentColor, "FragmentColor" },
			{ ShaderVariableTable::VertexWorldPosition, "VertexWorldPosition" },
			{ ShaderVariableTable::VertexViewWorldPosition, "VertexViewWorldPosition" },
			{ ShaderVariableTable::VertexProjectionViewWorldPosition, "VertexProjectionViewWorldPosition" },
			{ ShaderVariableTable::VertexWorldNormal, "VertexWorldNormal" },
			{ ShaderVariableTable::VertexViewWorldNormal, "VertexViewWorldNormal" },
			{ ShaderVariableTable::VertexTextureCoordinate0, "VertexTextureCoordinate0" },
			{ ShaderVariableTable::VertexTextureCoordinate1, "VertexTextureCoordinate1" },
			{ ShaderVariableTable::VertexTextureCoordinate2, "VertexTextureCoordinate2" },
			{ ShaderVariableTable::VertexTextureCoordinate3, "VertexTextureCoordinate3" },
			{ ShaderVariableTable::ViewDirection, "ViewDirection" },
			{ ShaderVariableTable::LightDirection, "LightDirection" },
			{ ShaderVariableTable::LightPosition, "LightPosition" },
			{ ShaderVariableTable::DiffuseColor, "DiffuseColor" }
		}
	};

	inline const char* GetShaderVariableName(ShaderVariableTable value)
	{
		for (auto& i : ShaderVariableNameMap) {
			if (i.m_code == value)
				return i.m_name;
		}

		return "";
	}

	template<ShaderDataType ParameterType, ShaderVariableTable GlobalVarialbe>
	struct ShaderInputVariable {

		static const ShaderVariableTable Parameter = GlobalVarialbe;
		static const ShaderDataType Type = ParameterType;

		static const std::string ToString() {
			std::stringstream stream;
			stream << "in " << GetDataTypeName(ParameterType) << " " << GetShaderVariableName(Parameter) << ";\n";
			return stream.str();
		}
	};

	template<typename ... GlobalVarialbes> struct ShaderGlobalVariableBlock;

	template<>
	struct ShaderGlobalVariableBlock < > {
		static const std::string ToString() { return "\n"; }
	};

	template<>
	struct ShaderGlobalVariableBlock <void> {
		static const std::string ToString() { return "\n"; }
	};

	template<typename GlobalVarialbe, typename ... GlobalVarialbes>
	struct ShaderGlobalVariableBlock<GlobalVarialbe, GlobalVarialbes...> : public ShaderGlobalVariableBlock < GlobalVarialbes... > {
		const std::string ToString() {
			std::stringstream stream;
			stream << GlobalVarialbe::ToString() << ShaderGlobalVariableBlock<GlobalVarialbes...>::ToString();
			return stream.str();
		}
	};

	template<ShaderDataType ParameterType, ShaderVariableTable GlobalVarialbe>
	struct ShaderOutputVariable {

		static const ShaderVariableTable Parameter = GlobalVarialbe;
		static const ShaderDataType Type = ParameterType;

		static const std::string ToString() {
			std::stringstream stream;
			stream << "out " << GetDataTypeName(ParameterType) << " " << GetShaderVariableName(Parameter) << ";\n";
			return stream.str();
		}
	};
}
PUNK_ENGINE_END

#endif // SHADER_VARIABLE_H
