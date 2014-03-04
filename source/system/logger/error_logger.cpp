//#include "system/errors/stack_trace.h"
//#include "error_logger.h"

//PUNK_ENGINE_BEGIN
//namespace System
//{
//    ErrorLogger::ErrorLogger(const Core::String &filename)
//        : FileLogger(filename)
//    {}

//    ErrorLogger::~ErrorLogger()
//    {}

//    void ErrorLogger::Write(const Core::String &value)
//    {
//        Stack stack;
//        Core::String error = Core::String("Error: {0}\nLocation:\n{1}").arg(value).arg(stack.GetStackTrace());
//        FileLogger::Write(error);
//        ConsoleConsumer::Write(error);
//    }
//}
//PUNK_ENGINE_END

//Punk::Engine::System::ILogger& out_error() {
//    static Punk::Engine::System::ErrorLogger* logger = nullptr;
//    if (!logger)
//        logger = new Punk::Engine::System::ErrorLogger("log");
//    return *logger;
//}
