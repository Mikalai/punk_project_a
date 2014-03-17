#ifndef _H_PUNK_OPENGL_RENDERABLE
#define _H_PUNK_OPENGL_RENDERABLE

#include <config.h>
#include <cstdint>
#include "irenderable.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    class PUNK_ENGINE_LOCAL Renderable : public IRenderable {
	public:
		Renderable();
        virtual ~Renderable();
        virtual void Bind(std::int64_t);
        virtual void Unbind();
        virtual void Render();
        virtual std::uint64_t GetMemoryUsage();
        virtual bool HasData() const;
	protected:
		int m_primitive_type;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_RENDERABLE
