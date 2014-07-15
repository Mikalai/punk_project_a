#include <math/mat4.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <core/iobject_impl.h>
#include <system/logger/module.h>
#include <attributes/geometry/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseGeometry(Core::Buffer& buffer, void* object)
    {
		Core::Pointer<Attributes::IGeometry> geometry{ (Attributes::IGeometry*)object, Core::DestroyObject };
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
			case WORD_ARMATURE_SCHEMA:
			{
				System::GetDefaultLogger()->Debug("Parse armature schema");
				Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				auto bone_stream = Core::QueryInterfacePtr<Attributes::IVertexBoneWeightStream>(geometry, Attributes::IID_IVertexBoneWeightStream);
				if (bone_stream)
					bone_stream->SetArmatureSchema(name);
			}
				break;
            case WORD_NAME:
            {
				System::GetDefaultLogger()->Debug("Parse name");
                Core::String name;
                parser->Parse(WORD_STRING, buffer, name);
                geometry->SetName(name);                
            }
                break;
            case WORD_VERTEX_POSITION:
            {
				System::GetDefaultLogger()->Debug("Parse vertex position");
                Math::vec3v v;
                parser->Parse(WORD_VEC3FV, buffer, v);
				auto position_stream = Core::QueryInterfacePtr<Attributes::IVertexPositionStream>(geometry, Attributes::IID_IVertexPositionStream);
				if (position_stream)
					position_stream->SetVertexPositions(v);
            }
                break;
            case WORD_NORMALS:
            {
				System::GetDefaultLogger()->Debug("Parse vertex normals");
                Math::vec3v n;
                parser->Parse(WORD_VEC3FV, buffer, n);
				auto normal_stream = Core::QueryInterfacePtr<Attributes::IVertexNormalStream>(geometry, Attributes::IID_IVertexNormalStream);
				if (normal_stream)
					normal_stream->SetVertexNormals(n);
            }
                break;
            case WORD_FACES:
            {
				System::GetDefaultLogger()->Debug("Parse faces");
                Math::ivec3v f;
				parser->Parse(WORD_VEC3IV, buffer, f);
				auto index_stream = Core::QueryInterfacePtr<Attributes::IFaceIndexStream>(geometry, Attributes::IID_IFaceIndexStream);
				if (index_stream)
					index_stream->SetTriangles(f);
            }
                break;
            case WORD_TEXTURE:
            {
				System::GetDefaultLogger()->Debug("Parse textures");
                std::vector<std::vector<std::array<Math::vec2, 3>>> t;
                parser->Parse(WORD_TEXTURE_COORD, buffer, &t);
				auto face_texture_stream = Core::QueryInterfacePtr<Attributes::IFaceTextureStream>(geometry, Attributes::IID_IFaceTextureStream);
				if (face_texture_stream)
					face_texture_stream->SetFaceTextureCoordinates(t);
            }
                break;
			case WORD_BONES_WEIGHTS:
			{	
				System::GetDefaultLogger()->Debug("Parse bone weights");
				std::vector<std::vector<std::pair<int, float>>> b;
				parser->Parse(WORD_BONES_WEIGHTS, buffer, (void*)&b);
				auto bone_stream = Core::QueryInterfacePtr<Attributes::IVertexBoneWeightStream>(geometry, Attributes::IID_IVertexBoneWeightStream);
				if (bone_stream)
					bone_stream->SetVertexBonesWeights(b);
			}
				break;
			case WORD_ARMATURE_MATRIX:
			{
				System::GetDefaultLogger()->Debug("Parse armature matrix");
				Math::mat4 m;
				parser->Parse<Math::mat4>(WORD_MATRIX4X4F, buffer, m);				
				auto bone_stream = Core::QueryInterfacePtr<Attributes::IVertexBoneWeightStream>(geometry, Attributes::IID_IVertexBoneWeightStream);
				if (bone_stream)
					bone_stream->SetArmatureOffset(m);
			}
				break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }

	PUNK_REGISTER_PARSER(WORD_STATIC_MESH, ParseGeometry);
	PUNK_REGISTER_PARSER(WORD_SKIN_MESH, ParseGeometry);
}
PUNK_ENGINE_END
