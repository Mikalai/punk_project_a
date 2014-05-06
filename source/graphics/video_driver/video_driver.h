#ifndef _H_PUNK_VIDEO_DRIVER
#define _H_PUNK_VIDEO_DRIVER

#include "ivideo_driver.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_LOCAL VideoDriver : public IVideoDriver {
	public:
        VideoDriver() = default;
        ~VideoDriver();        
        /*Frame* BeginFrame() override;
        void EndFrame(Frame* value) override;*/
	private:
        VideoDriver(const VideoDriver&) = delete;
        VideoDriver& operator = (const VideoDriver&) = delete;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER
