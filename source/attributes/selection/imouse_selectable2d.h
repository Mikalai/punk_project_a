#ifndef _H_IMOUSE_SELECTABLE2D
#define _H_IMOUSE_SELECTABLE2D

#include <config.h>
#include <math/vec2.h>
#include "imouse_selectable.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IMouseSelectable2D, "3BF3465B-5455-4391-83EE-A70C44C35C1F");

	class IMouseSelectable2D : public IMouseSelectable {
	public:		
		virtual float GetLocalX() const = 0;
		virtual float GetLocalY() const = 0;
		virtual const Math::vec2 GetLocalPosition() const = 0;
		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IMOUSE_SELECTABLE2D