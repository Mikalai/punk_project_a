#ifndef LOGGER_COMPONENT_H
#define LOGGER_COMPONENT_H

#include "core/component/module.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class MessageLogger;
    class WarningLogger;
    class ErrorLogger;

    class PUNK_ENGINE_LOCAL LoggerComponent : public Core::Component
    {
    public:
        LoggerComponent();

    protected:
        Core::Object* OnCreate(const Core::String &name, const Core::String &type, Core::Object **params) override;

        MessageLogger* m_msg_logger {nullptr};
        WarningLogger* m_wrn_logger {nullptr};
        ErrorLogger* m_err_logger {nullptr};
    };
}
PUNK_ENGINE_END

#endif // LOGGER_COMPONENT_H
