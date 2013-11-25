#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "logger.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class FileLogger : public virtual Logger
    {
    public:
        FileLogger(const Core::String& filename);
        virtual ~FileLogger();
        void Write(const Core::String &value) override;
    private:
        const Core::String m_filename;
    };
}
PUNK_ENGINE_END

#endif // FILE_LOGGER_H
