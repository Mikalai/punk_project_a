#ifndef PARSE_BONE_WEIGHT_H
#define PARSE_BONE_WEIGHT_H

#include <config.h>
#include <map>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace Loader {
    bool ParseBonesWeights(Core::Buffer& buffer, std::map<int, std::map<Core::String, float>>& value);
}
PUNK_ENGINE_END
#endif // PARSE_BONE_WEIGHT_H
