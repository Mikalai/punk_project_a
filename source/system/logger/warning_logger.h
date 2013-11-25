#ifndef WARNING_ERROR_H
#define WARNING_ERROR_H

#include "console_logger.h"
#include "file_logger.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_LOCAL WarningLogger : public ConsoleLogger, public FileLogger
    {
    public:
        WarningLogger(const Core::String& filename);
        virtual ~WarningLogger();
        void Write(const Core::String &value) override;
    };
}
PUNK_ENGINE_END

#endif // WARNING_ERROR_H
