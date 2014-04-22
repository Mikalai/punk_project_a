//#include <fstream>
//#include "String/buffer.h"
//#include "file_logger.h"

//PUNK_ENGINE_BEGIN
//namespace System
//{
//    FileLogger::FileLogger(const Core::String& filename)
//        : m_filename(filename)
//    {}

//    FileLogger::~FileLogger()
//    {}

//    void FileLogger::Write(const Core::String &value)
//    {
//        Logger::Write(value);
//        std::wofstream stream((char*)m_filename.ToAscii().Data(), std::ios_base::ate);
//        if (stream.is_open())
//        {
//            Core::Buffer buffer = value.ToUtf8();
//            stream.write((const wchar_t*)buffer.Data(), (std::streamsize)buffer.GetSize());
//        }
//    }
//}
//PUNK_ENGINE_END
