#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <punk_engine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShaderTest
{		
	using namespace Punk::Engine::Graphics;

	TEST_CLASS(UniformTests)
	{
	public:
		
		TEST_METHOD(GenerateUniformCode)
		{
			ShaderUniformBlock <
				ShaderUniformParameter < ShaderDataType::_mat4, ShaderUniformTable::WorldMatrix>,
				ShaderUniformParameter < ShaderDataType::_mat4, ShaderUniformTable::ViewMatrix >
			> s;

			std::string ss = s.ToString();
			std::cout << ss << std::endl;

			ShaderVertexAttributesBlock<
				ShaderAttribute<ShaderDataType::_vec4, ShaderAttributeTable::VertexPosition, 0>,
				ShaderAttribute<ShaderDataType::_vec4, ShaderAttributeTable::VertexNormal, 1>
			> s2;

			ss = s2.ToString();

			ShaderGlobalVariableBlock<void> s3;
			ss = s3.ToString();

			ShaderGlobalVariableBlock<
				ShaderInputVariable<ShaderDataType::_vec3, ShaderVariableTable::DiffuseColor>,
				ShaderInputVariable<ShaderDataType::_mat2x2, ShaderVariableTable::VertexBitangent>,
				ShaderOutputVariable<ShaderDataType::_vec4, ShaderVariableTable::VertexWorldPosition>
			> s4;

			ss = s4.ToString();
		}

	};
}