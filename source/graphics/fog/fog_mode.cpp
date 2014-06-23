#include <utility>
#include <string/module.h>
#include "fog_mode.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	using FogModeDesc = std::pair<FogMode, Core::String>;
	static const FogModeDesc g_fog_modes[] = {
		FogModeDesc(FogMode::Linear, L"Linear"),
		FogModeDesc(FogMode::Exponent, L"Exponent"),
		FogModeDesc(FogMode::Exponent2, L"Exponent2")
	};

	const Core::String AsString(const FogMode& v)
	{
		for (size_t i = 0; i != std::extent<decltype(g_fog_modes)>::value; ++i)
		{
			if (g_fog_modes[i].first == v)
				return g_fog_modes[i].second;
		}
		return L"ERROR";
	}

}
PUNK_ENGINE_END
