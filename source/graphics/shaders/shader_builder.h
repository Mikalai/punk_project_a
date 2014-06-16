#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#include <sstream>
#include <config.h>
#include <vector>
#include "shader_data_type.h"
#include "shader_type.h"
#include "shader_uniform_variable.h"
#include "shader_attribute.h"
#include "shader_variable.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{

	template<typename AttributesBlock, typename UniformBlocks, typename GlobalInput, typename GlobalOutput>
	struct ShaderBuilder {

		static const std::string ToString() {
			std::stringstream stream;
			stream << UniformBlocks::ToString() << std::endl;
			stream << AttributesBlock::ToString() << std::endl;			
			stream << GlobalInput::ToString() << std::endl;
			stream << GlobalOutput::ToString() << std::endl;
			return stream.str();
		}
	};



    /*class ShaderBuilder
    {
    public:
        ShaderBuilder();

        void Version(int value);
        int Version() const;

        void AddUniform(ShaderUniformTable value);
        void AddInputVariable(ShaderVarTable value);
        void AddOutputVaruable(ShaderVarTable value);

        const std::string ToString();

    private:
        int m_version;
        std::vector<ShaderUniformTable> m_uniforms;
        std::vector<ShaderVarTable> m_input;
        std::vector<ShaderVarTable> m_output;
    };*/
}
PUNK_ENGINE_END

#endif // SHADER_BUILDER_H
