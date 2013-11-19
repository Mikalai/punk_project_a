#ifndef WARNING_ERROR_H
#define WARNING_ERROR_H

#include "console_logger.h"
#include "file_logger.h"

namespace System
{
    class WarningLogger : public ConsoleLogger, public FileLogger
    {
    public:
        WarningLogger(const string& filename);
        virtual ~WarningLogger();
        void Write(const string &value) override;
    };
}

#endif // WARNING_ERROR_H
