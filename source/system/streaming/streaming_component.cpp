//#include "streaming_component.h"
//#include "async_loader_impl.h"

//namespace System
//{
//#ifdef USE_STREAMING_MODULE
//    REGISTER_COMPONENT(StreamingComponent, new StreamingComponent, {""})
//#endif

//#define ASYNC_LOADER String(L"async_loader")
//#define STREAMING String(L"streaming")

//    StreamingComponent::~StreamingComponent()
//    {
//        Clear();
//    }

//    void StreamingComponent::Clear()
//    {
//        delete m_loader;
//    }

//    void StreamingComponent::Create()
//    {
//        m_loader = new AsyncLoaderImpl(4);
//    }

//    void StreamingComponent::OnInitialize()
//    {
//        Create();
//    }

//    Object* StreamingComponent::OnGetService(const String &name)
//    {
//        if (name == ASYNC_LOADER)
//        {
//            return m_loader;
//        }
//        return nullptr;
//    }

//    const String StreamingComponent::GetName() const
//    {
//        return STREAMING;
//    }

//    const StringList StreamingComponent::GetServicesList() const
//    {
//        StringList res;
//        res.push_back(ASYNC_LOADER);
//        return res;
//    }
//}
