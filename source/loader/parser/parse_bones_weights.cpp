#include "parser.h"
#include "parse_bones_weights.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseBonesWeights(Core::Buffer& buffer, std::map<int, std::map<Core::String, float>>& value)
    {
        CHECK_START(buffer);

        while (1)
        {
            Core::String word = buffer.ReadWord();
            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;
            int vertex_id = word.ToInt32();
            Core::String bone_name = buffer.ReadWord();
            float weight = buffer.ReadWord().ToFloat();
            value[vertex_id][bone_name] = weight;
        }
        throw Error::LoaderException(L"Unable to parse vertex bones weights");
    }
}
PUNK_ENGINE_END
