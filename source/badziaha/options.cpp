#include "options.h"

Options::Options() {
	setOption(OptionType::EnableCheats, true);
	setOption(OptionType::TimeScale, 1.0f);
	setOption(OptionType::LocalFieldWidth, 64);
	setOption(OptionType::LocalFieldHeight, 64);
	setOption(OptionType::GlobalFieldHeight, 64);
	setOption(OptionType::GlobalFieldWidth, 64);
	setOption(OptionType::CellSize, 6250);

	load();
}

std::unique_ptr<Options> Options::m_instance;

void Options::load() {

}