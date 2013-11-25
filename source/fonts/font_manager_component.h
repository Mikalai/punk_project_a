#ifndef FONT_MANAGER_COMPONENT_H
#define FONT_MANAGER_COMPONENT_H

#include "system/component/module.h"

namespace Utility
{
    class FontBuilder;

    class FontManagerComponent : public System::Component
    {
    public:
        FontManagerComponent();
        virtual ~FontManagerComponent();
    protected:
        void OnInitialize() override;
        void OnDetach();
        System::Object* OnGetService(const System::string &) override;

    private:
        System::Object* Clone() const;

    private:
        void Clear();
        void Create();
        FontBuilder* m_font_builder;
    };
}

#endif // FONT_MANAGER_COMPONENT_H
