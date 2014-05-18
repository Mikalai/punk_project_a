#include "parser.h"
#include "parse_bones_weights.h"
#include <vector>
#include <utility>

PUNK_ENGINE_BEGIN
namespace Loader
{
	bool ParseBonesWeights(Core::Buffer& buffer, void* object) {

		Parser* parser = GetDefaultParser();
		std::vector<std::vector<std::pair<int, float>>>* bones = (std::vector<std::vector<std::pair<int, float>>>*)object;
        CHECK_START(buffer);

        while (1)
        {
            Core::String word = buffer.ReadWord();
			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_VERTEX_BONES_WEIGHTS:
				std::vector<std::pair<int, float>> weights;
				parser->Parse(WORD_VERTEX_BONES_WEIGHTS, buffer, (void*)&weights);
				bones->push_back(weights);
				break;
			}            
        }
        throw Error::LoaderException(L"Unable to parse vertex bones weights");
    }

	bool ParseVertexBonesWeights(Core::Buffer& buffer, void* object) {
		Parser* parser = GetDefaultParser();
		std::vector<std::pair<int, float>>* weights = (std::vector<std::pair<int, float>>*)object;

		CHECK_START(buffer);

		while (1) {
			Core::String word = buffer.ReadWord();
			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_VERTEX_INDEX:
			{
				std::uint32_t index;
				parser->Parse(WORD_UINT32, buffer, (void*)&index);
				break;
			}
			case WORD_WEIGHTS:
			{
				while (1) {
					Core::String word = buffer.ReadWord();
					if (word == Keyword[WORD_CLOSE_BRACKET].word)
						return true;
					int bone_index = buffer.ReadWord().ToInt32();
					float weight = buffer.ReadWord().ToFloat();
					weights->push_back(std::pair < int, float > {bone_index, weight});
				}
			}
			default:
				break;
			}
		}
	}

	PUNK_REGISTER_PARSER(WORD_BONES_WEIGHTS, ParseBonesWeights);
	PUNK_REGISTER_PARSER(WORD_VERTEX_BONES_WEIGHTS, ParseVertexBonesWeights);

}
PUNK_ENGINE_END
