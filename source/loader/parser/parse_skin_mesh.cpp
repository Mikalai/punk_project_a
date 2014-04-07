#include <attributes/skinning/module.h>
#include <attributes/data/skin_geometry.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_skin_mesh.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseSkinMesh(Core::Buffer& buffer, Attributes::SkinGeometry* geometry)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                geometry->SetName(name);                
            }
                break;
            case WORD_VERTEX_POSITION:
            {
                Attributes::SkinGeometry::Vertices v;
                ParseVector3fv(buffer, v);
                geometry->SetVertices(v);
            }
                break;
            case WORD_NORMALS:
            {
                Attributes::SkinGeometry::Normals n;
                ParseVector3fv(buffer, n);
                geometry->SetNormals(n);
            }
                break;
            case WORD_ARMATURE:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                geometry->SetArmatureName(name);
            }
                break;
            case WORD_FACES:
            {
                Attributes::SkinGeometry::Faces f;
                ParseVector3iv(buffer, f);
                geometry->SetFaces(f);
            }
                break;
            case WORD_TEXTURE:
            {
                Attributes::SkinGeometry::TextureMeshes t;
                ParseTextures(buffer, t);
                geometry->SetTextureMeshes(t);
            }
                break;
            case WORD_BONES_WEIGHT:
            {
                Attributes::SkinGeometry::BoneWeights b;
                ParseBonesWeights(buffer, b);
                geometry->SetBoneWeights(b);
            }
                break;
            case WORD_WORLD_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                geometry->SetWorldOffset(m);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }
}
PUNK_ENGINE_END
