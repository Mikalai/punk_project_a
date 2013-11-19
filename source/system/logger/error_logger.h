#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H

#include "console_logger.h"
#include "file_logger.h"

namespace System
{
    class ErrorLogger : public ConsoleLogger, public FileLogger
    {
    public:
        ErrorLogger(const string& filename);
        virtual ~ErrorLogger();
        void Write(const string &value) override;
    };
}

#endif // ERROR_LOGGER_H
