#include <system/factory/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <system/logger/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    Core::Pointer<Core::IObject> ParseAnything(Core::Buffer& buffer)
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
                    auto transform = System::CreateInstancePtr<Attributes::ITransform>(
						Attributes::CLSID_Transform, Attributes::IID_ITransform);
                    parser->Parse(WORD_TRANSFORM, buffer, transform.get());
					return transform;
				}
			}
			case WORD_ARMATURE_SCHEMA_TEXT:
			{
				Core::String word = buffer.ReadWord();
                auto schema = System::CreateInstancePtr<Attributes::IArmatureSchema>(
					Attributes::CLSID_ArmatureSchema, Attributes::IID_IArmatureSchema);
                parser->Parse(WORD_ARMATURE_SCHEMA, buffer, schema.get());
				schema->SetName(word);
				return schema;
			}
            case WORD_ARMATURETEXT:
            {
                Core::String word = buffer.ReadWord();         
                auto armature = System::CreateInstancePtr<Attributes::IArmature>(
					Attributes::CLSID_Armature, Attributes::IID_IArmature);
                parser->Parse(WORD_ARMATURE, buffer, armature.get());
				return armature;
            }
            case WORD_ACTIONTEXT:
            {
                Core::String word = buffer.ReadWord();
				auto animation = System::CreateInstancePtr<Attributes::IAnimation>(
					Attributes::CLSID_Animation, Attributes::IID_IAnimation);
                parser->Parse(WORD_ACTION, buffer, animation.get());
				animation->SetName(word);
				return animation;
            }
            case WORD_STATICMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto mesh = System::CreateInstancePtr<Attributes::IGeometry>(
					Attributes::CLSID_Geometry, Attributes::IID_IGeometry);

                parser->Parse(WORD_STATIC_MESH, buffer, mesh.get());
                mesh->SetName(word);
				return mesh;
            }
                break;
            case WORD_MATERIALTEXT:
            {                
                Core::String word = buffer.ReadWord();
                auto material = System::CreateInstancePtr<Attributes::IMaterial>(
					Attributes::CLSID_Material, Attributes::IID_IMaterial);
                parser->Parse(WORD_MATERIAL, buffer, material.get());
				return material;
            }
            case WORD_NAVIMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto navi_mesh = System::CreateInstancePtr<Attributes::INaviMesh>(
					Attributes::CLSID_NaviMesh, Attributes::IID_INaviMesh);
                parser->Parse(WORD_NAVI_MESH, buffer, navi_mesh.get());
				return navi_mesh;
            }
            case WORD_PATHTEXT:
            {
                Core::String word = buffer.ReadWord();
				auto path = System::CreateInstancePtr<Attributes::ICurvePath>(
					Attributes::CLSID_CurvePath, Attributes::IID_ICurvePath);
                parser->Parse(WORD_CURVE_PATH, buffer, path.get());
				return path;
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
                auto graph = System::CreateInstancePtr<SceneModule::IScene>(
					SceneModule::CLSID_Scene, SceneModule::IID_IScene);
                parser->Parse(WORD_SCENE_GRAPH, buffer, graph.get());
				return graph;
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
                auto mesh = System::CreateInstancePtr<Attributes::IGeometry>(
					Attributes::CLSID_Geometry, Attributes::IID_IGeometry);
                parser->Parse(WORD_SKIN_MESH, buffer, mesh.get());
                mesh->SetName(word);
				return mesh;
            }
            case WORD_DIRLIGHTTEXT:
            {
                Core::String word = buffer.ReadWord();
                auto light = System::CreateInstancePtr<Attributes::IDirectionalLight>(
					Attributes::CLSID_Light, Attributes::IID_IDirectionalLight);
                parser->Parse(WORD_DIRECTIONAL_LIGHT, buffer, light.get());
                light->SetName(word);
				return light;
            }
			case WORD_POINTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
                auto light = System::CreateInstancePtr<Attributes::IPointLight>(
					Attributes::CLSID_Light, Attributes::IID_IPointLight);
                parser->Parse(WORD_POINT_LIGHT, buffer, light.get());
                light->SetName(word);
				return light;
			}
			case WORD_SPOTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
                auto light = System::CreateInstancePtr<Attributes::ISpotLight>(
					Attributes::CLSID_Light, Attributes::IID_ISpotLight);
                parser->Parse(WORD_SPOT_LIGHT, buffer, light.get());
                light->SetName(word);
				return light;
			}
			case WORD_CAMERATEXT:
			{
				Core::String word = buffer.ReadWord();
				if (ParseKeyword(word) == WORD_PERSPECTIVE_CAMERA) {
                    auto camera = System::CreateInstancePtr<Attributes::IPerspectiveCamera>(
						Attributes::CLSID_PerspectiveCamera, Attributes::IID_IPerspectiveCamera);
                    parser->Parse(WORD_PERSPECTIVE_CAMERA, buffer, camera.get());
					return camera;
				}
				return Core::Pointer < Core::IObject > {nullptr, Core::DestroyObject};
			}
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        throw Error::LoaderException(L"Can't parse something");
    }
}
PUNK_ENGINE_END
