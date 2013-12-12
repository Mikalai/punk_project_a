#ifndef _H_PUNK_ERROR
#define _H_PUNK_ERROR

#include <cstdint>
#include "config.h"

namespace Punk {
	namespace Engine {
		namespace Core {
			namespace Error {
				class PUNK_ENGINE_API Exception {
				public:
					Exception(std::uint64_t code);
					std::uint64_t GetCode() const;
				private:
					std::uint64_t m_code;
				};
			}
		}
	}
}

#endif	//_H_PUNK_ERROR
