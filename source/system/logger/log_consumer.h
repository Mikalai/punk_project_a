#ifndef WARNING_ERROR_H
#define WARNING_ERROR_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{	
    class ILogConsumer
    {
    public:        
		virtual void Write(const Core::String& time, const Core::String& level, const Core::String &message) = 0;
    };
}
PUNK_ENGINE_END

#endif // WARNING_ERROR_H
