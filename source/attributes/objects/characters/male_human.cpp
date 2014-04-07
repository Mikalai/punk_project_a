#include "male_human_impl.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	MaleHuman::MaleHuman()
	{
		impl = new MaleHumanImpl;
	}
}
PUNK_ENGINE_END
