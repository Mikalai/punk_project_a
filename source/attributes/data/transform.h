#ifndef _H_PUNK_VIRTUAL_TRANSFORM
#define _H_PUNK_VIRTUAL_TRANSFORM

#include <math/mat4.h>
#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Transform : public Core::Object
	{
	public:

        Transform();
        Transform(const Transform&) = delete;
        Transform& operator = (const Transform&) = delete;
        Transform(const Math::mat4& m);
        virtual ~Transform();
		
		void Set(const Math::mat4& value) { m_transform = value; }
		const Math::mat4& Get() const { return m_transform; }
        Math::mat4& Get() { return m_transform; }        

	private:
		Math::mat4 m_transform;

	private:        
        PUNK_OBJECT(Transform)
	};    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TRANSFORM
