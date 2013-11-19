#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "logger.h"

namespace System
{
    class FileLogger : public virtual Logger
    {
    public:
        FileLogger(const string& filename);
        virtual ~FileLogger();
        void Write(const string &value) override;
    private:
        const string m_filename;
    };
}

#endif // FILE_LOGGER_H
