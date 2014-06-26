#include <utility>
#include <string/module.h>
#include <cstdint>
#include "blend_function.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{

    using BlendFunctionDesc = std::pair<BlendFunction, Core::String>;
	static const BlendFunctionDesc g_blend_functions[] = {
		BlendFunctionDesc(BlendFunction::SourceAlpha, L"Source alpha"),
		BlendFunctionDesc(BlendFunction::One, L"One"),
		BlendFunctionDesc(BlendFunction::OneMinusSrcAlpha, L"One minus source alpha")
	};

    const Core::String AsString(const BlendFunction& v)
	{
        for (std::size_t i = 0; i != std::extent<decltype(g_blend_functions)>::value; ++i)
		{
			if (g_blend_functions[i].first == v)
				return g_blend_functions[i].second;
		}
		return L"ERROR";
	}
}
PUNK_ENGINE_END
