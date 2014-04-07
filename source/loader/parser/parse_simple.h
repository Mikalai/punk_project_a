#ifndef PARSE_SIMPLE_H
#define PARSE_SIMPLE_H

#include <config.h>
#include <array>
#include <vector>
#include <map>
#include <math/module.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace Loader {
    extern bool ParseFloat(Core::Buffer& buffer, float& value);
    extern bool ParseInteger(Core::Buffer& buffer, int& value);
    extern bool ParseVector2f(Core::Buffer& buffer, Math::vec2& value);
    extern bool ParseVector3f(Core::Buffer& buffer, Math::vec3& value);
    extern bool ParseVector4f(Core::Buffer& buffer, Math::vec4& value);
    extern bool ParseVector2i(Core::Buffer& buffer, Math::ivec2& value);
    extern bool ParseVector3i(Core::Buffer& buffer, Math::ivec3& value);
    extern bool ParseVector4i(Core::Buffer& buffer, Math::ivec4& value);
    extern bool ParseQuaternionf(Core::Buffer& buffer, Math::quat& value);
    extern bool ParseMatrix4x4f(Core::Buffer& buffer, Math::mat4& value);
    extern bool ParseString(Core::Buffer& buffer, Core::String& value);
    extern bool ParseBlockedString(Core::Buffer& buffer, Core::String& value);
    extern bool ParseBlockedFloat(Core::Buffer& buffer, float& value);
    extern bool ParseBlockedInteger(Core::Buffer& buffer, int& value);
    extern bool ParseBlockedVector3f(Core::Buffer& buffer, Math::vec3& value);
    extern bool ParseBlockedQuaternionf(Core::Buffer& buffer, Math::quat& value);
    extern bool ParseBlockedVector4f(Core::Buffer& buffer, Math::vec4& value);
    extern bool ParseBlockedVector2i(Core::Buffer& buffer, Math::ivec2& value);
    extern bool ParseBlockedVector2f(Core::Buffer& buffer, Math::vec2& value);
    extern bool ParseBlockedMatrix4x4f(Core::Buffer& buffer, Math::mat4& value);
    extern bool ParseVector3fv(Core::Buffer& buffer, std::vector<Math::vec3>& value);
    extern bool ParseVector3iv(Core::Buffer& buffer, std::vector<Math::ivec3>& value);
    extern bool ParseVector4iv(Core::Buffer& buffer, std::vector<Math::ivec4>& value);
    extern bool ParseVector4Vector2iv(Core::Buffer& buffer, std::vector<std::array<Math::vec2, 4>>& value);
    extern bool ParseTextures(Core::Buffer& buffer, std::map<Core::String, std::vector<std::array<Math::vec2, 4>>>& value);
    extern bool ParseBonesWeights(Core::Buffer& buffer, std::map<int, std::map<Core::String, float>>& value);
}
PUNK_ENGINE_END

#endif // PARSE_SIMPLE_H
