#include <core/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <ai/module.h>
#include <system/logger/module.h>
#include "parse_directional_light.h"
#include "parse_terrain_mesh.h"
#include "parse_sun.h"
#include "parse_scene.h"
#include "parse_river.h"
#include "parse_curve_path.h"
#include "parse_navi_mesh.h"
#include "parse_material.h"
#include "parse_static_mesh.h"
#include "parse_skin_mesh.h"
#include "parse_armature.h"
#include "parse_action.h"
#include "parse_animation.h"
#include "parse_map_description.h"
#include "parse_transform.h"
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    Core::Object* ParseAnything(Core::Buffer& buffer)
    {		
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_MAPDESCTEXT:
            {				
                std::unique_ptr<Attributes::Terrain> terrain(new Attributes::Terrain);
                ParseMapDescription(buffer, terrain.get());
                return terrain.release();
            }
			case WORD_TRANSFORMTEXT:
			{
				Core::String word = buffer.ReadWord();
				if (word == L"transform") {
					std::unique_ptr<Attributes::Transform> transform(new Attributes::Transform);
					ParseTransform(buffer, transform.get());
					return transform.release();
				}
			}
            case WORD_ARMATURETEXT:
            {
                Core::String word = buffer.ReadWord();                
                std::unique_ptr<Attributes::Armature> armature;
                if (word == L"male_armature")
                {
                    armature.reset(new Attributes::HumanMaleArmature);
                }
                else
                {
                    armature.reset(new Attributes::Armature);
                }

                ParseArmature(buffer, armature.get());                
                return armature.release();
            }
            case WORD_ACTIONTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::Action> action;
                if (word == L"male_walk")
                    action.reset(new Attributes::ActionMaleWalk);
                else
                    action.reset(new Attributes::Action);
                ParseAction(buffer, action.get());
                return action.release();
            }
            case WORD_STATICMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::StaticGeometry> mesh(new Attributes::StaticGeometry);
                ParseStaticMesh(buffer, mesh.get());                
                mesh->SetName(word);
                return mesh.release();
            }
                break;
            case WORD_MATERIALTEXT:
            {                
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::Material> material(new Attributes::Material);
                ParseMaterial(buffer, material.get());                
                return material.release();
            }
            case WORD_NAVIMESHTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<AI::NaviMesh> navi_mesh(new AI::NaviMesh);
                ParseNaviMesh(buffer, navi_mesh.get());
                return navi_mesh.release();
            }
            case WORD_PATHTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<AI::CurvePath> path(new AI::CurvePath);
                ParseCurvePath(buffer, path.get());                
                return path.release();
            }
            case WORD_RIVERTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::River> river(new Attributes::River);
                ParseRiver(buffer, *river);                
                return river.release();
            }
            case WORD_SCENETEXT:
            {
                Scene::ISceneGraphUniquePtr graph = Scene::CreateScene();
                ParseSceneGraph(buffer, graph.get());
                return Cast<Core::Object*>(graph.release());
            }
            case WORD_SUNTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::Sun> sun(new Attributes::Sun);
                ParseSun(buffer, *sun);
                return sun.release();
            }
            case WORD_TERRAINTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::TerrainMesh> mesh(new Attributes::TerrainMesh);
                ParseTerrainMesh(buffer, *mesh);
                return mesh.release();
            }
            case WORD_SKINMESH_TEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::SkinGeometry> mesh(new Attributes::SkinGeometry);
                ParseSkinMesh(buffer, mesh.get());
                return mesh.release();
            }
            case WORD_DIRLIGHTTEXT:
            {
                Core::String word = buffer.ReadWord();
                std::unique_ptr<Attributes::DirectionalLight> light(new Attributes::DirectionalLight);
                ParseDirectionalLight(buffer, light.get());
                return light.release();
            }
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        throw Error::LoaderException(L"Can't parse something");
    }
}
PUNK_ENGINE_END
