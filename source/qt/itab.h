#ifndef _H_ITAB
#define _H_ITAB

#include <config.h>
#include <core/iobject.h>
#include "iwidget.h"

PUNK_ENGINE_BEGIN
namespace Gui {
	
	DECLARE_PUNK_GUID(IID_ITab, "F7F3B80F-206B-48B3-AFFE-E853CA46A2BA");

	class ITab : public IWidget {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITAB