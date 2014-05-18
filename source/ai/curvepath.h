#ifndef PUNK_AI_CURVEPATH_H
#define PUNK_AI_CURVEPATH_H

#include <config.h>
#include <core/iobject.h>
#include <math/vec3.h>
#include "icurvepath.h"

PUNK_ENGINE_BEGIN
namespace AI
{
    class PUNK_ENGINE_LOCAL CurvePath : public ICurvePath
    {
    public:
        CurvePath();
        CurvePath(const CurvePath&) = delete;
        CurvePath& operator = (const CurvePath&) = delete;
        virtual ~CurvePath();

		void QueryInterface(const Core::Guid& type, void** object) override;
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
        Core::String m_name;
		Math::ICurve* m_curve{ nullptr };
    private:
        PUNK_OBJECT_DEFAULT_IMPL3(CurvePath)
    };
}
PUNK_ENGINE_END

#endif // CURVEPATH_H
