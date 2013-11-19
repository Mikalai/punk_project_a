#include <fstream>
#include "file_logger.h"

namespace System
{
    FileLogger::FileLogger(const string& filename)
        : m_filename(filename)
    {}

    void FileLogger::Write(const string &value)
    {
        Logger::Write(value);
        std::wofstream stream(m_filename.ToStdString(), std::ios_base::ate);
        if (stream.is_open())
            stream << value;
    }
}
