#include "curvepath.h"

PUNK_ENGINE_BEGIN
namespace AI
{
    CurvePath::CurvePath()
		: m_container{ this, Core::GetRootObject() }
    {}

    CurvePath::~CurvePath()
    {}

    void CurvePath::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& CurvePath::GetName() const
    {
        return m_name;
    }    
}
PUNK_ENGINE_END
