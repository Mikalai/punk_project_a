#ifndef _H_TEMPERATURE
#define _H_TEMPERATURE

#include <memory>
#include <array>
#include <QtCore/qdatetime.h>

enum class WindDirection {
	Calm,
	North,
	NorthWest,
	West,
	SouthWest,
	South,
	SouthEast,
	East,
	NorthEast
};

inline const wchar_t* asString(WindDirection v) {
	switch (v)
	{
	case WindDirection::Calm:
		return L"Calm";
	case WindDirection::North:
		return L"North";
	case WindDirection::NorthWest:
		return L"North-West";
	case WindDirection::West:
		return L"West";
	case WindDirection::SouthWest:
		return L"South-West";
	case WindDirection::South:
		return L"South";
	case WindDirection::SouthEast:
		return L"South-East";
	case WindDirection::East:
		return L"East";
	case WindDirection::NorthEast:
		return L"North-East";
	default:
		return L"ERROR";
	}
}

enum class WeatherPhenomen {
	Clear,
	Brume,
	Fog,
	Rain,
	RainShowers,
	SnowRain,
	Snow,
	ShowShowers,
	Thunderstorm,
	Drizzle,
	Freeze,
	Hail
};

inline const wchar_t* asString(WeatherPhenomen v) {
	switch (v)
	{
	case WeatherPhenomen::Clear:
		return L"Clear";
	case WeatherPhenomen::Brume:
		return L"Brume";
	case WeatherPhenomen::Fog:
		return L"Fog";
	case WeatherPhenomen::Rain:
		return L"Rain";
	case WeatherPhenomen::RainShowers:
		return L"Rain showers";
	case WeatherPhenomen::SnowRain:
		return L"Show rain";
	case WeatherPhenomen::Snow:
		return L"Show";
	case WeatherPhenomen::ShowShowers:
		return L"Snow showers";
	case WeatherPhenomen::Thunderstorm:
		return L"Thunderstorm";
	case WeatherPhenomen::Drizzle:
		return L"Drizzle";
	case WeatherPhenomen::Freeze:
		return L"Freeze";
	case WeatherPhenomen::Hail:
		return L"Hail";
	default:
		return L"ERROR";
	}
}

enum class SkyState {
	Clear,
	Cloudy_1,
	Cloudy_2,
	PartlyCloudy_1,
	PartlyCloudy_2,
	VariableCloudy_1,
	VariableCloudy_2,
	VariableCloudy_3,
	BrokenClouds,
	Overcast
};

inline const wchar_t* asString(SkyState v) {
	switch (v)
	{
	case SkyState::Clear:
		return L"Clear";
	case SkyState::Cloudy_1:
		return L"Little cloude";
	case SkyState::Cloudy_2:
		return L"Cloudy";
	case SkyState::PartlyCloudy_1:
		return L"Little partly cloudy";
	case SkyState::PartlyCloudy_2:
		return L"Partly cloude";
	case SkyState::VariableCloudy_1:
		return L"Little variable cloudy";
	case SkyState::VariableCloudy_2:
		return L"Variable cloudy";
	case SkyState::VariableCloudy_3:
		return L"Significand variable cloudy";
	case SkyState::BrokenClouds:
		return L"Broken clouds";
	case SkyState::Overcast:
		return L"Overcast";
	default:
		return L"ERROR";
	}
}

struct WeatherStamp {
	QDateTime time;
	float temperature{ 0 };
	WindDirection wind_direction{ WindDirection::Calm };
	float wind_speed{ 0 };
	WeatherPhenomen phenomen{ WeatherPhenomen::Clear };
	SkyState sky_state{ SkyState::Clear };
	float visibility_range{ 1000 };
	float humitidy{ 15 };
	float pressure{ 1000 };

	const QString toString() const;
};

class Temperature {
public:

	Temperature();

	/*
	*	Get interpolated base weather point
	*/
	const WeatherStamp weather(const QDateTime& time);

	static Temperature* instance();
	static void destroy();

private:
	void load();

private:
	static std::unique_ptr<Temperature> m_instance;
	std::array<std::array<std::array<WeatherStamp, 8>, 31>, 12> m_stamps;
};

#endif	//	_H_TEMPERATURE