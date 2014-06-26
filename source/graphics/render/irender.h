#ifndef IRENDER_H
#define IRENDER_H

#include <config.h>
#include <core/iobject.h>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Math {
    class vec2;
    class mat4;
}

namespace Graphics {

	class IFrame;
    class Batch;
    class IFrameBuffer;
    class IVideoDriver;
	class IRenderQueue;
	class IRenderContextFactory;

	DECLARE_PUNK_GUID(IID_ILowLevelRender, "5B3310D7-3954-4047-ABF2-694B98355C79");

    class ILowLevelRender : public Core::IObject {
    public:
		virtual void Initialize(IVideoDriver* driver) = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;       
        virtual void SubmitBatch(Batch* batch) = 0;
        virtual const Math::vec2 FindZRange(const Math::mat4& view) = 0;
		virtual IFrame* BeginFrame() = 0;
		virtual void EndFrame() = 0;
		virtual IRenderQueue* GetRenderQueue() = 0;
		virtual IRenderContextFactory* GetRenderContextFactory() = 0;
    };

	using IRenderPointer = Core::Pointer < ILowLevelRender > ;
}
PUNK_ENGINE_END

#endif // IRENDER_H
