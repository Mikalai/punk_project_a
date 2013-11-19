#ifndef MESSAGE_LOGGER_H
#define MESSAGE_LOGGER_H

#include "file_logger.h"
#include "console_logger.h"

namespace System
{
    class MessageLogger: public ConsoleLogger, public FileLogger
    {
    public:
        MessageLogger(const string& filename);
        virtual ~MessageLogger();
        void Write(const string &value) override;
    };
}

#endif // MESSAGE_LOGGER_H
