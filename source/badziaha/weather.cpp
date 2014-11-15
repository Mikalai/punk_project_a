#include <iostream>
#include <math.h>
#include <cstdint>
#include <QtCore/qdatetime.h>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include "string_ex.h"
#include "weather.h"
#include "enum_helper.h"
#include "constants.h"

std::unique_ptr<Temperature> Temperature::m_instance;

enum WeatherHeader {
	DATE,
	HOUR,
	TEMPERATURE,
	WIND_DIRECTION,
	WIND_SPEED,
	WEATHER_STATE,
	SKY_STATE,
	VISIBILITY,
	HUMIDITY,
	PRESSURE
};

Temperature::Temperature() {
	load();
}

WindDirection wind_dir(QString s) {
	wchar_t buf[64];
	auto c = s.toWCharArray(buf);
	auto value = std::wstring(buf, buf+c);
	if (value == L"Южный")
		return WindDirection::South;
	if (value == L"Восточный")
		return WindDirection::East;
	if (value == L"Западный")
		return WindDirection::West;
	if (value == L"Северный")
		return WindDirection::North;
	if (value == L"Ю-З")
		return WindDirection::SouthWest;
	if (value == L"Ю-В")
		return WindDirection::SouthEast;
	if (value == L"С-З")
		return WindDirection::NorthWest;
	if (value == L"С-В")
		return WindDirection::NorthEast;
	if (value == L"Штиль")
		return WindDirection::Calm;
	
	qDebug("Unkown wind direction. Use calm by default");
	return WindDirection::Calm;
}

WeatherPhenomen weather_phenomen(QString s) {
	wchar_t buf[64];
	auto c = s.toWCharArray(buf);
	auto value = std::wstring(buf);
	if (s == "CL")
		return WeatherPhenomen::Clear;
	if (s == "BR")
		return WeatherPhenomen::Brume;
	if (s == "FG")
		return WeatherPhenomen::Fog;
	if (s == "RA")
		return WeatherPhenomen::Rain;
	if (s == "SHRA")
		return WeatherPhenomen::RainShowers;
	if (s == "SNRA")
		return WeatherPhenomen::SnowRain;
	if (s == "SN")
		return WeatherPhenomen::Snow;
	if (s == "SHSN")
		return WeatherPhenomen::ShowShowers;
	if (s == "TS")
		return WeatherPhenomen::Thunderstorm;
	if (s == "DZ")
		return WeatherPhenomen::Drizzle;
	if (s == "FZ")
		return WeatherPhenomen::Freeze;
	if (s == "HL")
		return WeatherPhenomen::Hail;

	qDebug("Unknown weather phenomen. Use clear by default");
	return WeatherPhenomen::Clear;

}

void Temperature::load() {
	int year = 2013;
	QString filename_header = ":/temperature/temperature/33041_2013-";
	for (int i = 0; i < 12; ++i) {
		QString filename = filename_header;
		if (i < 9) {
			filename += "0";
		} 
		filename += QString::number(i + 1) + ".csv";
		std::wcout << toWString(filename) << std::endl;
		QFile file{ filename };
		QTextStream stream{ &file };
		if (file.open(QIODevice::ReadOnly)) {
			while (!stream.atEnd()) {
				QString line = stream.readLine();
				QStringList data = line.split(";");
				int date = data[DATE].toInt()-1;
				int hour = data[HOUR].toInt();
				int index = hour / 3;	//format storage specific
				m_stamps[i][date][index].time = QDateTime{ QDate{ year, i + 1, date + 1 }, QTime{ hour, 0, 0 } };
				m_stamps[i][date][index].temperature = data[TEMPERATURE].toFloat();
				m_stamps[i][date][index].wind_direction = wind_dir(data[WIND_DIRECTION]);
				m_stamps[i][date][index].wind_speed = data[WIND_SPEED].toFloat();
				m_stamps[i][date][index].phenomen = weather_phenomen(data[WEATHER_STATE]);
				m_stamps[i][date][index].sky_state = enum_value<SkyState>(data[SKY_STATE].toInt());
				m_stamps[i][date][index].visibility_range = data[VISIBILITY].toFloat()*1000.0f;
				m_stamps[i][date][index].pressure = data[PRESSURE].toFloat();
				m_stamps[i][date][index].humitidy = data[HUMIDITY].toFloat();

				/*auto s = m_stamps[i][date][index].toString();
				auto stds = toWString(s);
				std::wcout << stds << std::endl;*/
			}
		}
	}
}

Temperature* Temperature::instance() {
	if (!m_instance.get())
		m_instance.reset(new Temperature);
	return m_instance.get();
}

void Temperature::destroy() {
	m_instance.reset(nullptr);
}

const QString WeatherStamp::toString() const {
	QStringList list;
	list.append(time.toString());
	list.append(QString::number(temperature, 'f', 1) + " C");
	list.append(QString::fromWCharArray(asString(wind_direction)));
	list.append(QString::number(wind_speed, 'f', 2) + " m/s");
	list.append(QString::fromWCharArray(asString(phenomen)));
	list.append(QString::fromWCharArray(asString(sky_state)));
	list.append(QString::number(visibility_range, 'f', 1) + " m");
	list.append(QString::number(humitidy, 'f', 1) + " %");
	list.append(QString::number(pressure, 'f', 1) + " Pa");
	list.append(QString::number(heatConvectionFactor(), 'f', 1) + " W/m^2/K")
	return list.join("; ");
}

const WeatherStamp Temperature::weather(const QDateTime& time) {
	int date1 = time.date().day();
	int month1 = time.date().month();
	int date2 = date1;
	int month2 = month1;
	int hour = time.time().hour();
	int start = hour / 3;
	int next = start + 1;
	if (next > 7) {
		next = 0;
		date2++;
		if (date2 > time.date().daysInMonth()) {
			date2 = 1;
			month2++;
			if (month2 > 12)
				month2 = 1;
		}
	}	

	auto s1 = m_stamps[month1-1][date1-1][start];
	auto d = s1.time.date();
	d.setDate(time.date().year(), d.month(), d.day());
	s1.time.setDate(d);
	auto s2 = m_stamps[month2-1][date2-1][next];
	std::wcout << toWString(time.toString()) << std::endl;
	std::wcout << toWString(s1.toString()) << std::endl;
	std::wcout << toWString(s2.toString()) << std::endl;
	auto q = s1.time.secsTo(time);
	std::cout << (std::uint64_t)q << std::endl;
	auto t = 1.0f - q / (3.0f * 60.0f * 60.0f);
	std::cout << t << std::endl;
	auto res = s1;
	res.time = time;
	res.temperature = s1.temperature*t + s2.temperature*(1.0f - t);
	res.humitidy = s1.humitidy*t + s2.humitidy*(1.0f - t);
	res.pressure = s1.pressure*t + s2.pressure*(1.0f - t);
	res.visibility_range = s1.visibility_range*t + s2.visibility_range*(1.0f - t);
	res.wind_speed = s1.wind_speed*t + s2.wind_speed*(1.0f - t);
	return res;
}

float HeatSource::power(WeatherStamp* w, const QPointF& p) const {
	if (m_is_sun) {
		return m_power;
	}
	else {
		auto r = (p - m_position).manhattanLength();
		auto s = 4 * Const::PI * r * r;
		return m_power / s;
	}
}

float WeatherStamp::heatConvectionFactor() const {
	if (wind_speed < 0.0f)
		return 0.0f;
	if (wind_speed > 10.0f)
		return 41.0f;
	if (wind_speed >= 0.0f && wind_speed <= 2.0f)
		return 3.0f + (26.0f - 3.0f) * wind_speed / 2.0f;
	if (wind_speed > 2.0f && wind_speed <= 8.0f)
		return 26.0f + (37.0f - 26.0f) * (wind_speed - 2.0f) / (8.0f - 2.0f);
	if (wind_speed > 8 && wind_speed <= 10.0f)
		return 37.0f + (41.0f - 37.0f) * (wind_speed - 8.0f) / (10.0f - 8.0f);
	return 0.0f;
}