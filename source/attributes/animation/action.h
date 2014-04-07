#ifndef _H_PUNK_UTILITY_ACTION
#define _H_PUNK_UTILITY_ACTION

#include <core/object.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class Animation;

	//	Animation is a child of Action
    class PUNK_ENGINE_API Action : public Core::Object
	{
	public:
		Action();
        Action(const Action&) = delete;
        Action& operator = (const Action&) = delete;
        virtual ~Action();

		int GetStartFrame() const { return m_start_frame; }
		int GetEndFrame() const { return m_end_frame; }

		void SetEndFrame(const int frame) { m_end_frame = frame; }
		void SetStartFrame(int frame) { m_start_frame = frame; }

        void SetName(Core::String& value);
        const Core::String& GetName() const;

	private:
		int m_start_frame;
		int m_end_frame;
        Core::String m_name;

        PUNK_OBJECT(Action)
	};
}
PUNK_ENGINE_END

#endif
