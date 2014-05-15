#ifndef _H_PUNK_VIRTUAL_DATA_DOOR
#define _H_PUNK_VIRTUAL_DATA_DOOR

#include "../../config.h"
#include "../../math/portal.h"
#include "../../system/object.h"
#include "../../opengl/renderable/renderable_data.h"

namespace Attributes
{
	class Location;

	class PUNK_ENGINE_API Door : public Core::IObject
	{
	public:
		enum State { CLOSED, OPENED };

	public:

		virtual void Save(Core::Buffer* buffer) const;
		virtual void Load(Core::Buffer* buffer);

		State GetState() const { return m_state; }
		void SetState(State value) { m_state = value; }

		const Math::Portal& GetPortal() const { return m_portal; }
		const Core::String& GetLocationName() const {return m_location_name; }

	private:

		State m_state;
		Math::Portal m_portal;
		Core::String m_location_name;		
	};
}

#endif	//	_H_PUNK_VIRTUAL_DATA_DOOR
