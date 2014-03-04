//#include "core/component/module.h"
//#include "message_logger.h"

//PUNK_ENGINE_BEGIN
//namespace System
//{
//    MessageLogger::MessageLogger(const Core::String &filename)
//        : FileLogger(filename)
//    {
//        m_clock = System::CreateClock();
//    }

//    MessageLogger::~MessageLogger()
//    {
//        System::DestroyClock(m_clock);
//    }

//    void MessageLogger::Write(const Core::String &value)
//    {
//        Core::String s = Core::String("{0}: Message> {1}").arg(m_clock->SysTimeNowAsLocal()).arg(value);
//        ConsoleConsumer::Write(s);
//        FileLogger::Write(s);
//    }
//}
//PUNK_ENGINE_END

//PUNK_ENGINE_API Punk::Engine::System::ILogger& out_message() {
//    static Punk::Engine::System::MessageLogger* logger = nullptr;
//    if (!logger)
//        logger = new Punk::Engine::System::MessageLogger("log");
//    return *logger;
//}
