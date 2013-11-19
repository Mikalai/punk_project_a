#include "logger_component.h"
#include "error_logger.h"
#include "message_logger.h"
#include "warning_logger.h"

namespace System
{
#ifdef USE_LOGGER_MODULE
    REGISTER_COMPONENT(LoggerComponent, new LoggerComponent, {"cofig"})
#endif


#define LOGGER_COMPONENT string(L"logger")
#define MESSAGE_LOGGER_SERVICE string(L"message")
#define WARNING_LOGGER_SERVICE string(L"warning")
#define ERROR_LOGGER_SERVICE string(L"error")

    LoggerComponent::~LoggerComponent()
    {
        Clear();
    }

    void LoggerComponent::Create()
    {
        const string filename = "log";  // TODO: should be read from config
        m_msg_logger = new MessageLogger(filename);
        m_wrn_logger = new WarningLogger(filename);
        m_err_logger = new ErrorLogger(filename);
    }

    void LoggerComponent::Clear()
    {
        delete m_msg_logger;
        m_msg_logger = nullptr;
        delete m_wrn_logger;
        m_wrn_logger = nullptr;
        delete m_err_logger;
        m_err_logger = nullptr;
    }

    void LoggerComponent::OnDetach()
    {
        Clear();
    }

    Object* LoggerComponent::OnGetService(const string& value)
    {
        if (value == MESSAGE_LOGGER_SERVICE)
            return m_msg_logger;
        if (value == WARNING_LOGGER_SERVICE)
            return m_wrn_logger;
        if (value == ERROR_LOGGER_SERVICE)
            return m_err_logger;
        return nullptr;
    }
}

System::ILogger& out_error()
{
    return *System::GetService<System::ILogger>(L"logger", L"error");
}

System::ILogger& out_message()
{
    return *System::GetService<System::ILogger>("logger", "message");
}

System::ILogger& out_warning()
{
    return *System::GetService<System::ILogger>("logger", "warning");
}
