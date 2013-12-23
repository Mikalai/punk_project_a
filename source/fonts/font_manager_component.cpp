//#include "font_manager_component.h"
//#include "font_builder.h"

//namespace Utility
//{
//    REGISTER_COMPONENT(FontManagerComponent, new FontManagerComponent, {""})

//#define FONT_MANAGER_COMPONENT Core::String(L"font_manager")
//#define FONT_BUILDER_SERVICE Core::String(L"font_builder")

//    FontManagerComponent::FontManagerComponent()
//    {
//        SetName("font_manager");
//        AddService(FONT_BUILDER_SERVICE);
//    }

//    FontManagerComponent::~FontManagerComponent()
//    {
//        Clear();
//    }

//    void FontManagerComponent::OnInitialize()
//    {
//        Create();
//    }

//    void FontManagerComponent::OnDetach()
//    {
//        Clear();
//    }

//    void FontManagerComponent::Create()
//    {
//        m_font_builder = new FontBuilder;
//        m_font_builder->Init();
//    }

//    void FontManagerComponent::Clear()
//    {
//        m_font_builder->Clone();
//    }

//    System::Object* FontManagerComponent::OnGetService(const Core::String & name)
//    {
//        if (name == FONT_BUILDER_SERVICE)
//            return m_font_builder;
//        return nullptr;
//    }
//}
