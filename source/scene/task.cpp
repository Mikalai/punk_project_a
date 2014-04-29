#include <typeinfo>
#include "task.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	Task::~Task() {}

	std::uint64_t Task::GetType() {
		return typeid(Task).hash_code();
	}

	std::uint64_t Task::Type() {
		return typeid(Task).hash_code();
	}
}
PUNK_ENGINE_END
