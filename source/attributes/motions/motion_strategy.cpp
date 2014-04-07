#include "motion_strategy.h"
#include <system/logger/module.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti MotionStrategy::Type{"Attributes.MotionStrategy",
                                    typeid(MotionStrategy).hash_code(),
        {&Core::Object::Type}};

	MotionStrategy::MotionStrategy()
        : Core::Object()
		, m_transform(0)
		, m_motion_type(MotionStrategyType::MOTION_STRATEGY_TYPE_NONE)
	{}

	MotionStrategy::~MotionStrategy()
	{}

//	bool MotionStrategy::Save(std::ostream& stream) const
//	{
//		if (!Core::Object::Save(stream))
//		{
//			out_error() << "Can't save motion strategy" << std::endl;
//			return false;
//		}

//		stream.write((char*)&m_motion_type, sizeof(m_motion_type));

//		return true;
//	}

//	bool MotionStrategy::Load(std::istream& stream)
//	{
//		if (!Core::Object::Load(stream))
//		{
//			out_error() << "Can't load motion strategy" << std::endl;
//			return false;
//		}

//		stream.read((char*)&m_motion_type, sizeof(m_motion_type));

//		return true;
//	}
}
PUNK_ENGINE_END
