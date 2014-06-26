#include <utility>
#include <string/module.h>
#include "light_model.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	using LightModelDesc = std::pair<LightModel, Core::String>;
	static const LightModelDesc g_light_models[] = {
		LightModelDesc(LightModel::PerVertexDiffuse, L"Per-vertex diffuse"),
		LightModelDesc(LightModel::PerFragmentDiffuse, L"Per-pixel diffuse"),
        LightModelDesc(LightModel::BumpMappingDiffuse, L"Bump mapping diffuse"),
	};

	const Core::String AsString(const LightModel& v)
	{
        for (std::size_t i = 0; i != std::extent<decltype(g_light_models)>::value; ++i)
		{
			if (g_light_models[i].first == v)
				return g_light_models[i].second;
		}
		return L"ERROR";
	}

	using LightAttenuationDesc = std::pair<LightAttenuation, Core::String>;
	static const LightAttenuationDesc g_light_attenuations[] = {
		LightAttenuationDesc(LightAttenuation::Constant, L"Constant"),
		LightAttenuationDesc(LightAttenuation::Linear, L"Linear"),
		LightAttenuationDesc(LightAttenuation::Quadratic, L"Quadratic")
	};

	const Core::String AsString(LightAttenuation value)
	{
        for (std::size_t i = 0; i != std::extent<decltype(g_light_attenuations)>::value; ++i)
		{
			if (g_light_attenuations[i].first == value)
				return g_light_attenuations[i].second;
		}
		return L"ERROR";
	}

	using LightTypeDesc = std::pair<LightType, Core::String>;
	static const LightTypeDesc g_light_types[] = {
		LightTypeDesc(LightType::Point, L"Point"),
        LightTypeDesc(LightType::Direction, L"Direction"),
		LightTypeDesc(LightType::Spot, L"Spot")
	};

	const Core::String AsString(LightType value)
	{
        for (std::size_t i = 0; i != std::extent<decltype(g_light_types)>::value; ++i)
		{
			if (g_light_types[i].first == value)
				return g_light_types[i].second;
		}
		return L"ERROR";
	}
}
PUNK_ENGINE_END
