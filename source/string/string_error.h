#ifndef _H_PUNK_STRING_ERROR
#define _H_PUNK_STRING_ERROR

#include <config.h>
#include <error/module.h>

PUNK_ENGINE_BEGIN
namespace Core {
	namespace Error {

		class PUNK_ENGINE_API StringException : public Exception {
		public:
			using Exception::Exception;
		};

		class PUNK_ENGINE_API StringConversionError : public Exception {
		public:
			using Exception::Exception;
		};

		class PUNK_ENGINE_API StringOutOfBufferRange : public Exception {
		public:
			using Exception::Exception;
		};

		static const std::uint64_t STR_ERR_UNKOWN = 0x0001000000000000;
		static const std::uint64_t STR_ERR_CONV_WCHAR_TO_ASCII = STR_ERR_UNKOWN + 1;
		static const std::uint64_t STR_ERR_CONV_WCHAR_TO_UTF8 = STR_ERR_UNKOWN + 2;
	}
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_STRING_ERROR
