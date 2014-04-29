#ifndef _H_SCENE_COMMAND
#define _H_SCENE_COMMAND

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Scene {
	class PUNK_ENGINE_API Command {
	public:
		virtual ~Command();
		virtual std::uint64_t GetType();
		static std::uint64_t Type();
	};
}
PUNK_ENGINE_END

#endif	//	_H_SCENE_COMMAND