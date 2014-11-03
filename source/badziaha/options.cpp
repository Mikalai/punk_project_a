#include "options.h"

Options::Options() {
	setOption(OptionType::EnableCheats, true);
}

std::unique_ptr<Options> Options::m_instance;