#ifndef _H_PUNK_VIRTUAL_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_MOTION_STRATEGY

#include <config.h>
#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Math { class mat4; }
namespace Attributes {

	class Transform;

	enum MotionStrategyType : char { MOTION_STRATEGY_TYPE_NONE, MOTION_STRATEGY_TYPE_STATIC };

    class PUNK_ENGINE_API MotionStrategy : public Core::Object
	{
	public:
		MotionStrategy();
		void SetTargetTransform(Transform* value) { m_transform = value; }
		Transform* GetTargetTransform() { return m_transform; }
		const Transform* GetTargetTransform() const { return m_transform; }
		MotionStrategyType GetMotionStrategyType() const { return m_motion_type; }

//		virtual void Save(Core::Buffer* buffer) const;
//		virtual void Load(Core::Buffer* buffer);
        virtual bool Update(int64_t current_time_us, int64_t delta_us) = 0;
		virtual ~MotionStrategy();

	protected:
		Transform* GetTransform() { return m_transform; }		
		const Transform* GetTransform() const { return m_transform; }
		void SetMotionStrategyType(MotionStrategyType value) { m_motion_type = value; }
	private:
        MotionStrategyType m_motion_type {MotionStrategyType::MOTION_STRATEGY_TYPE_NONE};
        Transform* m_transform {nullptr};

        PUNK_OBJECT(MotionStrategy)
	};	
}
PUNK_ENGINE_END

#endif
