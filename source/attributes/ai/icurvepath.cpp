#include <system/factory/module.h>
#include <math/vec3.h>
#include "icurvepath.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL CurvePath : public ICurvePath
	{
	public:
		CurvePath();
		CurvePath(const CurvePath&) = delete;
		CurvePath& operator = (const CurvePath&) = delete;
		virtual ~CurvePath();


		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ICurvePath
		void SetName(const Core::String& value) override;
		const Core::String& GetName() const override;
		void AddSpline(Math::ISpline* value) override;
		void AddSplines(const std::vector<Math::ISpline*>& value) override;
		float GetTotalLength() const override;
		const Math::vec3 At(float t) override;
		std::uint32_t GetSplinesCount() const override;
		const Math::ISpline* GetSpline(std::uint32_t index) const override;
		void Clear() override;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		Core::Pointer<Math::ICurve> m_curve{ nullptr, Core::DestroyObject };
	};


	void CurvePath::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ICurvePath});
	}

	std::uint32_t CurvePath::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t CurvePath::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

    CurvePath::CurvePath()
    {
        m_curve = System::CreateInstancePtr<Math::ICurve>(Math::CLSID_Curve, Math::IID_ICurve);
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

	PUNK_REGISTER_CREATOR(CLSID_CurvePath, (System::CreateInstance<CurvePath, ICurvePath>));
}
PUNK_ENGINE_END
