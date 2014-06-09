#ifndef SHADER_DATA_TYPE_H
#define SHADER_DATA_TYPE_H

#include <array>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class ShaderDataType {
        _void,
        _bool,
        _int,
        _uint,
        _float,
        _vec2,
        _vec3,
        _vec4,
        _bvec2,
        _bvec3,
        _bvec4,
        _ivec2,
        _ivec3,
        _ivec4,
        _uvec2,
        _uvec3,
        _uvec4,
        _mat2,
        _mat3,
        _mat4,
        _mat2x2,
        _mat2x3,
        _mat2x4,
        _mat3x2,
        _mat3x3,
        _mat3x4,
        _mat4x2,
        _mat4x3,
        _mat4x4,
        _sampler1d,
        _sampler2d,
        _sampler3d,
        _samplerCube,
        _sampler2dRect,
        _sampler1dShadow,
        _sampler2dShadow,
        _sampler1dArray,
        _sampler2dArray,
        _sampler1dArrayShadow,
        _sampler2dArrayShadow,
        _samplerBuffer,
        _sampler2DMS,
        _sampler2DMSArray,
        _isampler1d,
        _isampler2d,
        _isampler3d,
        _isamplerCube,
        _isampler2dRect,
        _isampler1dArray,
        _isampler2dArray,
        _isamplerBuffer,
        _isampler2DMS,
        _isampler2DMSArray,
        _usampler1d,
        _usampler2d,
        _usampler3d,
        _usamplerCube,
        _usampler2dRect,
        _usampler1dArray,
        _usampler2dArray,
        _usamplerBuffer,
        _usampler2DMS,
        _usampler2DMSArray,
		TotalCount
    };

	constexpr int GetIndex(const ShaderDataType value) {
		return (int)value;
	}

	struct ShaderDataTypeNameMapping {
		ShaderDataType m_code;
		const char* m_name;
	};

	const std::array < ShaderDataTypeNameMapping, GetIndex(ShaderDataType::TotalCount) > ShaderDataTypeMap{
			{
				{ ShaderDataType::_void, "void" },
				{ ShaderDataType::_bool, "bool" },
				{ ShaderDataType::_int, "int" },
				{ ShaderDataType::_uint, "uint" },
				{ ShaderDataType::_float, "float" },
				{ ShaderDataType::_vec2, "vec2" },
				{ ShaderDataType::_vec3, "vec3" },
				{ ShaderDataType::_vec4, "vec4" },
				{ ShaderDataType::_bvec2, "bvec2" },
				{ ShaderDataType::_bvec3, "bvec3" },
				{ ShaderDataType::_bvec4, "bvec4" },
				{ ShaderDataType::_ivec2, "ivec2" },
				{ ShaderDataType::_ivec3, "ivec3" },
				{ ShaderDataType::_ivec4, "ivec4" },
				{ ShaderDataType::_uvec2, "uvec2" },
				{ ShaderDataType::_uvec3, "uvec3" },
				{ ShaderDataType::_uvec4, "uvec4" },
				{ ShaderDataType::_mat2, "mat2" },
				{ ShaderDataType::_mat3, "mat3" },
				{ ShaderDataType::_mat4, "mat4" },
				{ ShaderDataType::_mat2x2, "mat2x2" },
				{ ShaderDataType::_mat2x3, "mat2x3" },
				{ ShaderDataType::_mat2x4, "mat2x4" },
				{ ShaderDataType::_mat3x2, "mat3x2" },
				{ ShaderDataType::_mat3x3, "mat3x3" },
				{ ShaderDataType::_mat3x4, "mat3x4" },
				{ ShaderDataType::_mat4x2, "mat4x2" },
				{ ShaderDataType::_mat4x3, "mat4x3" },
				{ ShaderDataType::_mat4x4, "mat4x4" },
				{ ShaderDataType::_sampler1d, "sampler1d" },
				{ ShaderDataType::_sampler2d, "sampler2d" },
				{ ShaderDataType::_sampler3d, "sampler3d" },
				{ ShaderDataType::_samplerCube, "samplerCube" },
				{ ShaderDataType::_sampler2dRect, "sampler2dRect" },
				{ ShaderDataType::_sampler1dShadow, "sampler1dShadow" },
				{ ShaderDataType::_sampler2dShadow, "sampler2dShadow" },
				{ ShaderDataType::_sampler1dArray, "sampler1dArray" },
				{ ShaderDataType::_sampler2dArray, "sampler2dArray" },
				{ ShaderDataType::_sampler1dArrayShadow, "sampler1dArrayShadow" },
				{ ShaderDataType::_sampler2dArrayShadow, "sampler2dArrayShadow" },
				{ ShaderDataType::_samplerBuffer, "samplerBuffer" },
				{ ShaderDataType::_sampler2DMS, "sampler2DMS" },
				{ ShaderDataType::_sampler2DMSArray, "sampler2DMSArray" },
				{ ShaderDataType::_isampler1d, "isampler1d" },
				{ ShaderDataType::_isampler2d, "isampler2d" },
				{ ShaderDataType::_isampler3d, "isampler3d" },
				{ ShaderDataType::_isamplerCube, "isamplerCube" },
				{ ShaderDataType::_isampler2dRect, "isampler2dRect" },
				{ ShaderDataType::_isampler1dArray, "isampler1dArray" },
				{ ShaderDataType::_isampler2dArray, "isampler2dArray" },
				{ ShaderDataType::_isamplerBuffer, "isamplerBuffer" },
				{ ShaderDataType::_isampler2DMS, "isampler2DMS" },
				{ ShaderDataType::_isampler2DMSArray, "isampler2DMSArray" },
				{ ShaderDataType::_usampler1d, "usampler1d" },
				{ ShaderDataType::_usampler2d, "usampler2d" },
				{ ShaderDataType::_usampler3d, "usampler3d" },
				{ ShaderDataType::_usamplerCube, "usamplerCube" },
				{ ShaderDataType::_usampler2dRect, "usampler2dRect" },
				{ ShaderDataType::_usampler1dArray, "usampler1dArray" },
				{ ShaderDataType::_usampler2dArray, "usampler2dArray" },
				{ ShaderDataType::_usamplerBuffer, "usamplerBuffer" },
				{ ShaderDataType::_usampler2DMS, "usampler2DMS" },
				{ ShaderDataType::_usampler2DMSArray, "usampler2DMSArray" }
			}
	};

	inline const char* GetDataTypeName(ShaderDataType value) {
		for (auto& i : ShaderDataTypeMap) {
			if (i.m_code == value)
				return i.m_name;
		}
		return "";
	}

}
PUNK_ENGINE_END

#endif // SHADER_DATA_TYPE_H
