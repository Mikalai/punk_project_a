#include "curvepath.h"

PUNK_ENGINE_BEGIN
namespace AI
{
	Core::Rtti CurvePathType{ "AI.CurvePath", typeid(CurvePath).hash_code(), { Core::Object::Type() } };

	Core::Rtti* CurvePath::Type() {
		return &CurvePathType;
	}

    CurvePath::CurvePath()
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
