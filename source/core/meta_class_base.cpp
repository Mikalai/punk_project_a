//#include <memory>
//#include "object.h"
//#include "meta_class_base.h"

//namespace Punk {
//    namespace Engine {
//        namespace Core {

//        }
//    }
//}
////    std::map<size_t, Object*(*)()> Factory::m_creator;
////    std::map<size_t, void (*)(Buffer*, const Object*)> Factory::m_saver;
////    std::map<size_t, void (*)(Buffer*, Object*)> Factory::m_loader;

////    Object* Factory::Create(unsigned id)
////    {
////        return m_creator[id]();
////    }

////    void Factory::Save(Buffer* buffer, const Object* o)
////    {
////        m_saver[o->GetType()->GetId()](buffer, o);
////    }

////    Object* Factory::Load(Buffer* buffer)
////    {
////        unsigned code = buffer->ReadUnsigned32();
////        std::unique_ptr<Object> o(m_creator[code]());
////        m_loader[code](buffer, o.get());
////        return o.release();
////    }

////    void Factory::AddChild(size_t id, Object* (*F)())
////    {
////        if (id == 0)
////            return;
////        m_creator[id] = F;
////    }

////    void Factory::AddChild(size_t id, void (*F)(Buffer*, const Object*))
////    {
////        if (id == 0)
////            return;
////        m_saver[id] = F;
////    }

////    void Factory::AddChild(size_t id, void (*F)(Buffer*, Object*))
////    {
////        if (id == 0)
////            return;
////        m_loader[id] = F;
////    }
