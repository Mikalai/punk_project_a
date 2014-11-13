#include "options.h"

Options::Options() {
	setOption(OptionType::EnableCheats, true);
	setOption(OptionType::TimeScale, 1.0f);
}

std::unique_ptr<Options> Options::m_instance;