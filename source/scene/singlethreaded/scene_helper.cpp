//#include "scene_helper.h"
//#include "node.h"

//namespace SceneModule
//{
//    const Math::mat4 GetGlobalMatrix(const Core::Object* object)
//    {
//        Math::mat4 res;
//        if (object->GetOwner() == nullptr)
//            return res;
//        std::vector<const Attributes::Transform*> transforms;
//        const Core::Object* owner = object;
//        while (1)
//        {
//            if (!owner)
//                break;
//            const Scene::Node* transform = As<const Scene::Node*>(owner);
//            if (transform)
//            {
//                const Core::Object* data = transform->GetData();
//                if (data && data->GetType()->IsEqual(&Attributes::Transform::Info.Type))
//                    transforms.push_back((Attributes::Transform*)transform->GetData());
//            }
//            owner = owner->GetOwner();
//        }
//        for (auto it = transforms.rbegin(); it != transforms.rend(); ++it)
//        {
//            res *= (*it)->Get();
//        }
//        return res;
//    }
//}
