//#include "logger_component.h"
//#include "error_logger.h"
//#include "message_logger.h"
//#include "warning_logger.h"

//PUNK_ENGINE_BEGIN
//namespace System
//{
//    REGISTER_COMPONENT(LoggerComponent);

//#define LOGGER_COMPONENT Core::String(L"logger")
//#define MESSAGE_LOGGER_SERVICE Core::String(L"message")
//#define WARNING_LOGGER_SERVICE Core::String(L"warning")
//#define ERROR_LOGGER_SERVICE Core::String(L"error")

//    LoggerComponent::LoggerComponent()
//        : Core::Component(LOGGER_COMPONENT, {MESSAGE_LOGGER_SERVICE, WARNING_LOGGER_SERVICE, ERROR_LOGGER_SERVICE}) {}

//    Core::Object* LoggerComponent::OnCreate(const Core::String& name, const Core::String& type, Core::Object** params)
//    {
//        (void)params;
//        Core::Object* o {nullptr};
//        if (type == MESSAGE_LOGGER_SERVICE)
//            o = new MessageLogger(name + ".log");
//        if (type == WARNING_LOGGER_SERVICE)
//            o = new WarningLogger(name + ".log");
//        if (type == ERROR_LOGGER_SERVICE)
//            o = new ErrorLogger(name + ".log");
//        if (o)
//            o->SetName(name);
//        return o;
//    }
//}
//PUNK_ENGINE_END

//Punk::Engine::System::ILogger& out_error()
//{
//    return *Punk::Engine::Core::Acquire<Punk::Engine::System::ILogger>("logger", L"errors", L"error");
//}

//Punk::Engine::System::ILogger& out_message()
//{
//    return *Punk::Engine::Core::Acquire<Punk::Engine::System::ILogger>("logger", "messages", "message");
//}

//Punk::Engine::System::ILogger& out_warning()
//{
//    return *Punk::Engine::Core::Acquire<Punk::Engine::System::ILogger>("logger", "warnings", "warning");
//}

