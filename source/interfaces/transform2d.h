#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <config.h>
#include <core/iobject.h>
#include <math/forward.h>

PUNK_ENGINE_BEGIN

DECLARE_PUNK_GUID(IID_ITransform2D, "D9A81233-703B-4110-9BD0-CC63F55311C4");

class ITransform2D : public Core::IObject {
public:
    virtual Math::point2d GetRelativePosition() const = 0;
    virtual void SetRelativePosition(const Math::point2d& value) = 0;
    virtual const Math::mat2 GetMatrix() const = 0;
    virtual void SetMatrix(const Math::mat2& value) = 0;
};

PUNK_ENGINE_END

#endif // TRANSFORM2D_H
