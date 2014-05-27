#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "ilight.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_ISpotLight, "179A7B61-C0CD-4BB3-9C39-1D3DB75E2511");

    class ISpotLight : public virtual ILight {
    public:
    };
}
PUNK_ENGINE_END

#endif // SPOT_LIGHT_H
