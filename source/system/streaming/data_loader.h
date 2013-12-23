#ifndef _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER
#define _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER

#include <config.h>
#include "streaming_result.h"

PUNK_ENGINE_BEGIN
namespace System
{
	class PUNK_ENGINE_API AbstractDataLoader
	{
	public:
		virtual ~AbstractDataLoader() {}
		
		/**
		*	when 0 returns it means an error
		*/
        virtual StreamingStepResult Load() = 0;
		
		/**
		*	when 0 returns it means an error
		*/
        virtual StreamingStepResult Decompress(void** data, unsigned* size) = 0;

		/**
		*	when 0 returns it means an error
		*/
        virtual StreamingStepResult Destroy() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER
