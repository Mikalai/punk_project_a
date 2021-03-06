#include "../../scene/module.h"
#include "parse_functions.h"

namespace IoModule
{
//    bool ParseLocationIndoor(Core::Buffer& buffer, SceneModule::LocationIndoorNode* location)
//    {
//        CHECK_START(buffer);
//        while (!buffer.IsEnd())
//        {
//            Core::String word = buffer.ReadWord();
//            switch (ParseKeyword(word))
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NAME:
//            {
//                Core::String name;
//                ParseBlockedString(buffer, name);
//                location->SetName(name);
//                location->SetStorageName(name);
//            }
//            case WORD_LOCAL_MATRIX:
//            {
//                Math::mat4 m;
//                ParseBlockedMatrix4x4f(buffer, m);
//                location->SetLocalMatrix(m);
//            }
//                break;
//            case WORD_CONVEX_MESH:
//            {
//                Math::ConvexShapeMesh mesh;
//                ParseConvexMesh(buffer, mesh);
//                location->SetConvexMesh(mesh);
//            }
//                break;
//            case WORD_MATERIAL_NODE:
//            {
//                std::unique_ptr<SceneModule::MaterialNode> node(new SceneModule::MaterialNode);
//                ParseMaterialNode(buffer, node.get());
//                location->Add(node.release());
//            }
//                break;
//            case WORD_TRANSFORM_NODE:
//            {
//                std::unique_ptr<SceneModule::TransformNode> node(new SceneModule::TransformNode);
//                ParseTransformNode(buffer, node.get());
//                location->Add(node.release());
//            }
//                break;
//            case WORD_PORTAL_NODE:
//            {
//                std::unique_ptr<SceneModule::PortalNode> node(new SceneModule::PortalNode);
//                ParsePortalNode(buffer, node.get());
//                location->Add(node.release());
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
}
