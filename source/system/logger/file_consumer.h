#ifndef _H_FILE_CONSUMER
#define _H_FILE_CONSUMER

#include <fstream>
#include "log_consumer.h"

PUNK_ENGINE_BEGIN
namespace System {
	class PUNK_ENGINE_LOCAL FileConsumer : public ILogConsumer
	{
	public:
		FileConsumer();
		virtual ~FileConsumer();
		void Write(const Core::String &value) override;
	private:
		std::wofstream m_stream;
	};
}
PUNK_ENGINE_END

#endif // _H_FILE_CONSUMER
