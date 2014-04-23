#include <array>
#include <vector>
#include <system/logger/module.h>
#include <string/module.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/mat3.h>
#include <math/mat2.h>
#include <math/quat.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    ///	Returns false if couldn't find open bracket in the buffer
    bool CheckIntegrity(Core::Buffer& buffer)
    {
        if (Parse(buffer.ReadWord()) != WORD_OPEN_BRACKET)
            return false;
        return true;
    }

    /// This function convert a string representation of the file into code
    KeywordCode Parse(const Core::String& word)
    {
        for (unsigned i = 0; i < sizeof(Keyword)/sizeof(Record); i++)
        {
			if (word == Keyword[i].word) {
				System::GetDefaultLogger()->Info(Core::String("Parse {0} ({1})").arg(Keyword[i].word).arg(Keyword[i].code));
				return Keyword[i].code;
			}
        }
        throw Error::LoaderException(Core::String("Unknown keyword {0}").arg(word));
        return WORD_BAD_KEYWORD;
    }

    bool ParseFloat(Core::Buffer& buffer, float& value)
    {
        value = buffer.ReadWord().ToFloat();
        return true;
    }

    bool ParseInteger(Core::Buffer& buffer, int& value)
    {
        value = buffer.ReadWord().ToInt32();
        return true;
    }

    bool ParseVector2f(Core::Buffer& buffer, Math::vec2& value)
    {
        value[0] = buffer.ReadWord().ToFloat();
        value[1] = buffer.ReadWord().ToFloat();
        return true;
    }

    bool ParseVector3f(Core::Buffer& buffer, Math::vec3& value)
    {
        value[0] = buffer.ReadWord().ToFloat();
        value[1] = buffer.ReadWord().ToFloat();
        value[2] = buffer.ReadWord().ToFloat();
        return true;
    }

    bool ParseQuaternionf(Core::Buffer &buffer, Math::quat &value)
    {
        value[0] = buffer.ReadWord().ToFloat();
        value[1] = buffer.ReadWord().ToFloat();
        value[2] = buffer.ReadWord().ToFloat();
        value[3] = buffer.ReadWord().ToFloat();
        return true;
    }

    bool ParseVector4f(Core::Buffer& buffer, Math::vec4& value)
    {
        value[0] = buffer.ReadWord().ToFloat();
        value[1] = buffer.ReadWord().ToFloat();
        value[2] = buffer.ReadWord().ToFloat();
        value[3] = buffer.ReadWord().ToFloat();
        return true;
    }

    bool ParseVector2i(Core::Buffer& buffer, Math::ivec2& value)
    {
        value[0] = buffer.ReadWord().ToInt32();
        value[1] = buffer.ReadWord().ToInt32();
        return true;
    }

    bool ParseVector3i(Core::Buffer& buffer, Math::ivec3& value)
    {
        value[0] = buffer.ReadWord().ToInt32();
        value[1] = buffer.ReadWord().ToInt32();
        value[2] = buffer.ReadWord().ToInt32();
        return true;
    }

    bool ParseVector4i(Core::Buffer& buffer, Math::ivec4& value)
    {
        value[0] = buffer.ReadWord().ToInt32();
        value[1] = buffer.ReadWord().ToInt32();
        value[2] = buffer.ReadWord().ToInt32();
        value[3] = buffer.ReadWord().ToInt32();
        return true;
    }

    bool ParseMatrix4x4f(Core::Buffer& buffer, Math::mat4& value)
    {
        for (int i = 0; i < 16; ++i)
            value[i] = buffer.ReadWord().ToFloat();
        value = value.Transposed();
        return true;
    }

    bool ParseString(Core::Buffer& buffer, Core::String& value)
    {
        value = buffer.ReadWord();
        return true;
    }

    bool ParseBlockedString(Core::Buffer& buffer, Core::String& value)
    {
        CHECK_START(buffer);
        if (!ParseString(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked string");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedFloat(Core::Buffer& buffer, float& value)
    {
        CHECK_START(buffer);
        if (!ParseFloat(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked float number");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedInteger(Core::Buffer& buffer, int& value)
    {
        CHECK_START(buffer);
        if (!ParseInteger(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked float number");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedVector3f(Core::Buffer& buffer, Math::vec3& value)
    {
        CHECK_START(buffer);
        if (!ParseVector3f(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked vec3f");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedQuaternionf(Core::Buffer &buffer, Math::quat &value)
    {
        CHECK_START(buffer);
        if (!ParseQuaternionf(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked quat");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedVector4f(Core::Buffer& buffer, Math::vec4& value)
    {
        CHECK_START(buffer);
        if (!ParseVector4f(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked vec3f");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedVector2i(Core::Buffer& buffer, Math::ivec2& value)
    {
        CHECK_START(buffer);
        if (!ParseVector2i(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked vec3f");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedVector2f(Core::Buffer& buffer, Math::vec2& value)
    {
        CHECK_START(buffer);
        if (!ParseVector2f(buffer, value))
            throw Error::LoaderException(L"Unable to parse blocked vec3f");
        CHECK_END(buffer);
        return true;
    }

    bool ParseBlockedMatrix4x4f(Core::Buffer& buffer, Math::mat4& value)
    {
        CHECK_START(buffer);
        if (!ParseMatrix4x4f(buffer, value))
            throw Error::LoaderException(L"Unable to parse mat4f");
        CHECK_END(buffer);
        return true;
    }

    bool ParseVector3fv(Core::Buffer& buffer, std::vector<Math::vec3>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            float x = buffer.ReadWord().ToFloat();
            float y = buffer.ReadWord().ToFloat();
            float z = buffer.ReadWord().ToFloat();

            Math::vec3 v;
            v.Set(x,y,z);

            value.push_back(v);
        }
        throw Error::LoaderException(L"Unable to parse array ov vec3f");
    }

    bool ParseVector3iv(Core::Buffer& buffer, std::vector<Math::ivec3>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int x = buffer.ReadWord().ToInt32();
            int y = buffer.ReadWord().ToInt32();
            int z = buffer.ReadWord().ToInt32();

            Math::ivec3 v;
            v.Set(x,y,z);

            value.push_back(v);
        }
        throw Error::LoaderException(L"Unable to parse vector of vec3i");
    }

    bool ParseVector4iv(Core::Buffer& buffer, std::vector<Math::ivec4>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int x = word.ToInt32();
            int y = buffer.ReadWord().ToInt32();
            int z = buffer.ReadWord().ToInt32();
            int w = buffer.ReadWord().ToInt32();

            Math::ivec4 v;
            v.Set(x,y,z,w);

            value.push_back(v);
        }
        throw Error::LoaderException(L"Unable to parse vector of vec4i");
    }

    bool ParseVector4Vector2iv(Core::Buffer& buffer, std::vector<std::array<Math::vec2, 4>>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            float u1 = word.ToFloat();
            float v1 = buffer.ReadWord().ToFloat();
            float u2 = buffer.ReadWord().ToFloat();
            float v2 = buffer.ReadWord().ToFloat();
            float u3 = buffer.ReadWord().ToFloat();
            float v3 = buffer.ReadWord().ToFloat();
            float u4 = buffer.ReadWord().ToFloat();
            float v4 = buffer.ReadWord().ToFloat();

            std::array<Math::vec2, 4> v;
            v[0].Set(u1, v1);
            v[1].Set(u2, v2);
            v[2].Set(u3, v3);
            v[3].Set(u4, v4);

            value.push_back(v);
        }
        throw Error::LoaderException(L"Unable to parse vector of vec4<vec2f>");
    }

}
PUNK_ENGINE_END
