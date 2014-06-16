#ifndef _H_GL_VERTEX_COMPONENT_TYPE
#define _H_GL_VERTEX_COMPONENT_TYPE

#include <config.h>
#include "graphics/primitives/vertex_component.h"
#include "graphics/opengl/module.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		constexpr int VertexComponentTypeToOpenGL(const VertexComponentType& type) {
			int res = -1;
			switch (type){
				case VertexComponentType::No:
				res = -1;
				case VertexComponentType::Float:
					res = GL_FLOAT;
				case VertexComponentType::Uint32:
					res = GL_UNSIGNED;
				case VertexComponentType::Uint16:
					res = GL_SHORT;
			}
			return res;
		}
	}
}
PUNK_ENGINE_END

#endif	//	_H_GL_VERTEX_COMPONENT_TYPE