#include <utility>
#include <string/module.h>
#include "shadow_model.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    using ShadowModelDesc = std::pair<ShadowModel, Core::String>;
    static const ShadowModelDesc g_shadow_models[] = {
        ShadowModelDesc(ShadowModel::ShadowMapSimple, L"ShadowMapSimple"),
        ShadowModelDesc(ShadowModel::ShadowMapCascade, L"ShadowMapCascade")
    };

    const Core::String AsString(ShadowModel value)
    {
        for (size_t i = 0; i != std::extent<decltype(g_shadow_models)>::value; ++i)
        {
            if (g_shadow_models[i].first == value)
                return g_shadow_models[i].second;
        }
        return L"ERROR";
    }
}
PUNK_ENGINE_END
