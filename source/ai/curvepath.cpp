#include <core/factory.h>
#include "curvepath.h"

PUNK_ENGINE_BEGIN
namespace AI
{
    CurvePath::CurvePath()
		: m_container{ this, Core::GetRootObject() }		
    {
		Core::GetFactory()->CreateInstance(Math::IID_ICurve, (void**)&m_curve);
	}

    CurvePath::~CurvePath()
    {
		if (m_curve)
			m_curve->Release();
	}

    void CurvePath::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& CurvePath::GetName() const
    {
        return m_name;
    }    

	void CurvePath::AddSpline(Math::ISpline* value) {
		m_curve->AddSpline(value);
	}

	void CurvePath::AddSplines(const std::vector<Math::ISpline*>& value) {
		m_curve->AddSplines(value);
	}

	float CurvePath::GetTotalLength() const {
		return m_curve->GetTotalLength();
	}

	const Math::vec3 CurvePath::At(float t) {
		return m_curve->At(t);
	}

	std::uint32_t CurvePath::GetSplinesCount() const {
		return m_curve->GetSplinesCount();
	}

	const Math::ISpline* CurvePath::GetSpline(std::uint32_t index) const {
		return m_curve->GetSpline(index);
	}

	void CurvePath::Clear() {
		m_curve->Clear();
	}

	void CurvePath::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == Math::IID_ICurve ||
			type == IID_ICurvePath) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	void CreateCurvePath(void** object) {
		if (!object)
			return;
		*object = (void*)(new CurvePath);
	}

	PUNK_REGISTER_CREATOR(IID_ICurvePath, CreateCurvePath);
}
PUNK_ENGINE_END
