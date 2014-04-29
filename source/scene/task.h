#ifndef _H_PUNK_SCENE_TASK
#define _H_PUNK_SCENE_TASK

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Scene {
	class PUNK_ENGINE_API Task {
	public:
		virtual ~Task();
		std::uint64_t GetType();
		static std::uint64_t Type();
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SCENE_TASK
