#include "punk_error.h"

PUNK_ENGINE_BEGIN
namespace Core {
	namespace Error {

		Exception::Exception(std::uint64_t code)
			: m_code(code) {}

		std::uint64_t Exception::GetCode() const {
			return m_code;

		}
	}
}
PUNK_ENGINE_END
