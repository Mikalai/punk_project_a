#include <typeinfo>
#include "command.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	Command::~Command(){}

	std::uint64_t Command::GetType() {
		return typeid(Command).hash_code();
	}

	std::uint64_t Command::Type() {
		return typeid(Command).hash_code();
	}

}
PUNK_ENGINE_END
