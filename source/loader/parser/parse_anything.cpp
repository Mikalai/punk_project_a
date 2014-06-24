#include <core/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <ai/module.h>
#include <system/logger/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    Core::IObject* ParseAnything(Core::Buffer& buffer)
    {		
		Parser* parser = GetDefaultParser();
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            /*case WORD_MAPDESCTEXT:
            {				
                std::unique_ptr<Attributes::Terrain> terrain(new Attributes::Terrain);
                parser->Parse(WORD_MAPDESCTEXT, buffer, (void)terrain.get());
                return terrain.release();
            }*/
			case WORD_TRANSFORMTEXT:
			{
				Core::String word = buffer.ReadWord();
				if (word == L"transform") {
                    auto transform = Core::CreateInstancePtr<Attributes::ITransform>(Attributes::IID_ITransform);
                    parser->Parse(WORD_TRANSFORM, buffer, transform.get());
                    return transform.release();
				}
			}
			case WORD_ARMATURE_SCHEMA_TEXT:
			{
				Core::String word = buffer.ReadWord();
                auto schema = Core::CreateInstancePtr<Attributes::IArmatureSchema>(Attributes::IID_IArmatureSchema);
                parser->Parse(WORD_ARMATURE_SCHEMA, buffer, schema.get());
				schema->SetName(word);
                return schema.release();
			}
            case WORD_ARMATURETEXT:
            {
                Core::String word = buffer.ReadWord();         
                auto armature = Core::CreateInstancePtr<Attributes::IArmature>(Attributes::IID_IArmature);
                parser->Parse(WORD_ARMATURE, buffer, armature.get());
                return armature.release();
            }
            case WORD_ACTIONTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto animation = Core::CreateInstancePtr<Attributes::IAnimation>(Attributes::IID_IAnimation);
                parser->Parse(WORD_ACTION, buffer, animation.get());
				animation->SetName(word);
                return animation.release();
            }
            case WORD_STATICMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto mesh = Core::CreateInstancePtr<Attributes::IGeometry>(Attributes::IID_IGeometry);
                parser->Parse(WORD_STATIC_MESH, buffer, mesh.get());
                mesh->SetName(word);
                return mesh.release();
            }
                break;
            case WORD_MATERIALTEXT:
            {                
                Core::String word = buffer.ReadWord();
                auto material = Core::CreateInstancePtr<Attributes::IMaterial>(Attributes::IID_IMaterial);
                parser->Parse(WORD_MATERIAL, buffer, material.get());
                return material.release();
            }
            case WORD_NAVIMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto navi_mesh = Core::CreateInstancePtr<AI::INaviMesh>(AI::IID_INaviMesh);
                parser->Parse(WORD_NAVI_MESH, buffer, navi_mesh.get());
                return navi_mesh.release();
            }
            case WORD_PATHTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto path = Core::CreateInstancePtr<AI::ICurvePath>(AI::IID_ICurvePath);
                parser->Parse(WORD_CURVE_PATH, buffer, path.get());
                return path.release();
            }
            /*case WORD_RIVERTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::River> river(new Attributes::River);
                ParseRiver(buffer, *river);                
                return river.release();
            }*/
            case WORD_SCENETEXT:
            {
                auto graph = Core::CreateInstancePtr<SceneModule::IScene>(SceneModule::IID_IScene);
                parser->Parse(WORD_SCENE_GRAPH, buffer, graph.get());
                return graph.release();
            }
           /* case WORD_SUNTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::Sun> sun(new Attributes::Sun);
                ParseSun(buffer, *sun);
                return sun.release();
            }*/
            /*case WORD_TERRAINTEXT:
            {
                Core::String word = buffer.ReadWord();
				Attributes::ITerrainMesh > mesh{ nullptr };
                ParseTerrainMesh(buffer, *mesh);
                return mesh.release();
            }*/
            case WORD_SKINMESH_TEXT:
            {
                Core::String word = buffer.ReadWord();
                auto mesh = Core::CreateInstancePtr<Attributes::IGeometry>(Attributes::IID_IGeometry);
                parser->Parse(WORD_SKIN_MESH, buffer, mesh.get());
                mesh->SetName(word);
                return mesh.get();
            }
            case WORD_DIRLIGHTTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto light = Core::CreateInstancePtr<Attributes::IDirectionalLight>(Attributes::IID_IDirectionalLight);
                parser->Parse(WORD_DIRECTIONAL_LIGHT, buffer, light.get());
                light->SetName(word);
                return light.release();
            }
			case WORD_POINTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
                auto light = Core::CreateInstancePtr<Attributes::IPointLight>(Attributes::IID_IPointLight);
                parser->Parse(WORD_POINT_LIGHT, buffer, light.get());
                light->SetName(word);
                return light.release();
			}
			case WORD_SPOTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
                auto light = Core::CreateInstancePtr<Attributes::ISpotLight>(Attributes::IID_ISpotLight);
                parser->Parse(WORD_SPOT_LIGHT, buffer, light.get());
                light->SetName(word);
                return light.release();
			}
			case WORD_CAMERATEXT:
			{
				Core::String word = buffer.ReadWord();
				if (ParseKeyword(word) == WORD_PERSPECTIVE_CAMERA) {
                    auto camera = Core::CreateInstancePtr<Attributes::IPerspectiveCamera>(Attributes::IID_IPerspectiveCamera);
                    parser->Parse(WORD_PERSPECTIVE_CAMERA, buffer, camera.get());
                    return camera.release();
				}
				return nullptr;
			}
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        throw Error::LoaderException(L"Can't parse something");
    }
}
PUNK_ENGINE_END
