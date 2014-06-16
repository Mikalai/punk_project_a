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
		Core::IFactory* factory = Core::GetFactory();
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
					Attributes::ITransform* transform;
					factory->CreateInstance(Attributes::IID_ITransform, (void**)&transform);
					parser->Parse(WORD_TRANSFORM, buffer, (void*)transform);
					return transform;
				}
			}
			case WORD_ARMATURE_SCHEMA_TEXT:
			{
				Core::String word = buffer.ReadWord();
				Attributes::IArmatureSchema* schema;
				factory->CreateInstance(Attributes::IID_IArmatureSchema, (void**)&schema);
				parser->Parse(WORD_ARMATURE_SCHEMA, buffer, (void*)schema);
				schema->SetName(word);
				return schema;
			}
            case WORD_ARMATURETEXT:
            {
                Core::String word = buffer.ReadWord();         
				Attributes::IArmature* armature;
				factory->CreateInstance(Attributes::IID_IArmature, (void**)&armature);
				parser->Parse(WORD_ARMATURE, buffer, (void*)armature);
				return armature;
            }
            case WORD_ACTIONTEXT:
            {
                Core::String word = buffer.ReadWord();
                Attributes::IAction* action;
				factory->CreateInstance(Attributes::IID_IAction, (void**)&action);
                parser->Parse(WORD_ACTION, buffer, action);
                return action;
            }
            case WORD_STATICMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
				Attributes::IGeometry* mesh{ nullptr };
				factory->CreateInstance(Attributes::IID_IGeometry, (void**)&mesh);
				parser->Parse(WORD_STATIC_MESH, buffer, mesh);
                mesh->SetName(word);
                return mesh;
            }
                break;
            case WORD_MATERIALTEXT:
            {                
                Core::String word = buffer.ReadWord();
				Attributes::IMaterial* material{ nullptr };
				factory->CreateInstance(Attributes::IID_IMaterial, (void**)&material);
				parser->Parse(WORD_MATERIAL, buffer, material);
				return material;
            }
            case WORD_NAVIMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
				AI::INaviMesh* navi_mesh{ nullptr };
				parser->Parse(WORD_NAVI_MESH, buffer, navi_mesh);
				return navi_mesh;
            }
            case WORD_PATHTEXT:
            {
                Core::String word = buffer.ReadWord();
				AI::ICurvePath* path{ nullptr };
				Core::GetFactory()->CreateInstance(AI::IID_ICurvePath, (void**)&path);
				parser->Parse(WORD_CURVE_PATH, buffer, path);
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
				SceneModule::IScene* graph{ nullptr };
				Core::GetFactory()->CreateInstance(SceneModule::IID_IScene, (void**)&graph);
				parser->Parse(WORD_SCENE_GRAPH, buffer, graph);
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
				Attributes::IGeometry* mesh{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_IGeometry, (void**)&mesh);
				parser->Parse(WORD_SKIN_MESH, buffer, mesh);
                return mesh;
            }
            case WORD_DIRLIGHTTEXT:
            {
                Core::String word = buffer.ReadWord();
				Attributes::IDirectionalLight* light{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_IDirectionalLight, (void**)&light);
                parser->Parse(WORD_DIRECTIONAL_LIGHT, buffer, light);
                return light;
            }
			case WORD_POINTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
				Attributes::IPointLight* light{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_IPointLight, (void**)&light);
				parser->Parse(WORD_POINT_LIGHT, buffer, light);
				return light;
			}
			case WORD_SPOTLIGHTTEXT:
			{
				Core::String word = buffer.ReadWord();
				Attributes::ISpotLight* light{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_ISpotLight, (void**)&light);
				parser->Parse(WORD_SPOT_LIGHT, buffer, light);
				return light;
			}
			case WORD_CAMERATEXT:
			{
				Core::String word = buffer.ReadWord();
				if (ParseKeyword(word) == WORD_PERSPECTIVE_CAMERA) {
					Attributes::IPerspectiveCamera* camera{ nullptr };
					Core::GetFactory()->CreateInstance(Attributes::IID_IPerspectiveCamera, (void**)&camera);
					parser->Parse(WORD_PERSPECTIVE_CAMERA, buffer, camera);
					return camera;
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
