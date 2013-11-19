#ifndef LOGGER_COMPONENT_H
#define LOGGER_COMPONENT_H

#include "system/component/module.h"

namespace System
{
    class MessageLogger;
    class WarningLogger;
    class ErrorLogger;

    class LoggerComponent : public Component
    {
    public:
        virtual ~LoggerComponent();

    protected:
        void OnDetach() override;
        void OnInitialize() override;
        Object* OnGetService(const string &);

    private:
        void Clear();
        void Create();

        MessageLogger* m_msg_logger;
        WarningLogger* m_wrn_logger;
        ErrorLogger* m_err_logger;
    };
}

#endif // LOGGER_COMPONENT_H
