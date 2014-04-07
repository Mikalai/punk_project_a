#ifndef PUNK_AI_CURVEPATH_H
#define PUNK_AI_CURVEPATH_H

#include <config.h>
#include <core/object.h>
#include <math/spline.h>
#include <math/curve.h>

PUNK_ENGINE_BEGIN
namespace AI
{
    class PUNK_ENGINE_API CurvePath : public Math::Curve, public Core::Object
    {
    public:
        CurvePath();
        CurvePath(const CurvePath&) = delete;
        CurvePath& operator = (const CurvePath&) = delete;
        virtual ~CurvePath();

        void SetName(const Core::String& value);
        const Core::String& GetName() const;
    private:
        Core::String m_name;
    private:
        PUNK_OBJECT(CurvePath)
    };
}
PUNK_ENGINE_END

#endif // CURVEPATH_H
