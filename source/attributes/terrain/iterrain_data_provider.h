#ifndef _H_ITERRAIN_DATA_PROVIDER
#define _H_ITERRAIN_DATA_PROVIDER

#include <config.h>
#include <core/iobject.h>
#include <string/buffer.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ITerrainDataProvider, "2E7926DA-19D9-4211-826A-AC6100E68FA4");
	DECLARE_PUNK_GUID(CLSID_GeneratedTerrainDataProvider, "2A06899F-312C-4D29-98D9-AC49A844AFC8");
	DECLARE_PUNK_GUID(CLSID_FileTerrainDataProvider, "2A06899F-312C-4D29-98D9-AC49A844AFC8");

	class ITerrainDataProvider : public Core::IObject {
	public:
		virtual void SetDestinationBuffer(std::uint32_t width, std::uint32_t height, float* buffer) = 0;
		virtual void SetVisibleRange(float l_min, float b_min, float l_max, float b_max) = 0;
		virtual void SetDetailsLevel(int level) = 0;
		virtual void UpdateBuffer() = 0;
	};
}
PUNK_ENGINE_END
#endif	//	 _H_ITERRAIN_DATA_PROVIDER