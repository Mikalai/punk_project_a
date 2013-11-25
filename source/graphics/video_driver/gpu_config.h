#ifndef _H_PUNK_GPU_CONFIG
#define _H_PUNK_GPU_CONFIG

#ifdef _WIN32
#include <windows.h>
#endif

#include "config.h"

#define PUNK_GPU_USE_OPENGL

PUNK_ENGINE_BEGIN
namespace Graphics
{
	struct PUNK_ENGINE_API Config
	{
        bool disable_3d_graphics {false};
        int view_width {1024};
        int view_height {768};
        int view_left {0};
        int view_top {0};
        bool fullscreen {false};
        int refresh_rate {60};
        int bits_per_pixel {32};
        int shadow_map_width {512};
        int shadow_map_height {512};
        bool use_multisampling {false};
        int multisampling_depth {2};
        bool use_coveragesampling {false};
        int coverage_depth {4};


#ifdef _WIN32
        HWND m_hwnd;
#endif
		
		Config();			
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_CONFIG
