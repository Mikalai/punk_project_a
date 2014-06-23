#ifndef _H_PUNK_RENDER_PASS
#define _H_PUNK_RENDER_PASS

#include <config.h>
#include <map>
#include <vector>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class Batch;    
    class CoreState;
    class IVideoDriver;
    class ITexture2D;
    class IRenderable;

	class RenderPass
	{
	public:
        RenderPass(IVideoDriver* driver, std::vector<Batch*> batches);
		~RenderPass();
		void Run();

	private:
        IVideoDriver* m_driver;
		std::vector<Batch*> m_batches;
        ITexture2D* m_shadow_map;

		void SetUpShadowMap();
		void GenerateShadowMap(std::vector<Batch*>& batches);
        void OnePass(IRenderable* renderable, CoreState* state);
	};

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_RENDEER
