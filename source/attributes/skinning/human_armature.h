//#ifndef _H_PUNK_VIRTUAL_HUMAN_ARMATURE
//#define _H_PUNK_VIRTUAL_HUMAN_ARMATURE
//
//#include "armature.h"
//
//PUNK_ENGINE_BEGIN
//namespace Attributes
//{
//	enum HumanArmaturePart {
//        HUMAN_BEGIN = 0,
//        HUMAN_ROOT = 0,
//		HUMAN_HEAD,
//		HUMAN_NECK,
//		HUMAN_COLLAR_LEFT,
//		HUMAN_COLLAR_RIGHT,
//		HUMAN_UPPER_ARM_LEFT,
//		HUMAN_UPPER_ARM_RIGHT,
//		HUMAN_LOWER_ARM_LEFT,
//		HUMAN_LOWER_ARM_RIGHT,
//		HUMAN_PALM_LEFT,
//		HUMAN_PALM_RIGHT,
//		HUMAN_BIG_FINGER_A_LEFT,
//		HUMAN_BIG_FINGER_A_RIGHT,
//		HUMAN_BIG_FINGER_B_LEFT,
//		HUMAN_BIG_FINGER_B_RIGHT,
//		HUMAN_BIG_FINGER_C_LEFT,
//		HUMAN_BIG_FINGER_C_RIGHT,
//		HUMAN_FINGER_1_A_LEFT,
//		HUMAN_FINGER_1_A_RIGHT,
//		HUMAN_FINGER_1_B_LEFT,
//		HUMAN_FINGER_1_B_RIGHT,
//		HUMAN_FINGER_1_C_LEFT,
//		HUMAN_FINGER_1_C_RIGHT,
//		HUMAN_FINGER_2_A_LEFT,
//		HUMAN_FINGER_2_A_RIGHT,
//		HUMAN_FINGER_2_B_LEFT,
//		HUMAN_FINGER_2_B_RIGHT,
//		HUMAN_FINGER_2_C_LEFT,
//		HUMAN_FINGER_2_C_RIGHT,
//		HUMAN_FINGER_3_A_LEFT,
//		HUMAN_FINGER_3_A_RIGHT,
//		HUMAN_FINGER_3_B_LEFT,
//		HUMAN_FINGER_3_B_RIGHT,
//		HUMAN_FINGER_3_C_LEFT,
//		HUMAN_FINGER_3_C_RIGHT,
//		HUMAN_FINGER_4_A_LEFT,
//		HUMAN_FINGER_4_A_RIGHT,
//		HUMAN_FINGER_4_B_LEFT,
//		HUMAN_FINGER_4_B_RIGHT,
//		HUMAN_FINGER_4_C_LEFT,
//		HUMAN_FINGER_4_C_RIGHT,
//		HUMAN_CHEST,
//		HUMAN_STOMACH,
//		HUMAN_BASE,
//		HUMAN_PELVIS,
//		HUMAN_THIGH_LEFT,
//		HUMAN_THIGH_RIGHT,
//		HUMAN_LOWER_LEG_LEFT,
//		HUMAN_LOWER_LEG_RIGHT,
//		HUMAN_FOOT_LEFT,
//		HUMAN_FOOT_RIGHT,
//		HUMAN_TOE_LEFT,
//		HUMAN_TOE_RIGHT,
//		HUMAN_END
//	};
//
//	class PUNK_ENGINE_API HumanArmature : public Armature
//	{
//	public:
//        HumanArmature();
//        HumanArmature(const HumanArmature&) = delete;
//        HumanArmature& operator = (const HumanArmature&) = delete;
//        virtual ~HumanArmature();
//
//		virtual void UpdateHierarchy() override;
//
//		int GetBoneIndexByName(HumanArmaturePart value);
//
//	private:
//		int m_bone_index[HUMAN_END - HUMAN_BEGIN];
//
//        PUNK_OBJECT_DEFAULT_IMPL(HumanArmature)
//	};    
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_VIRTUAL_HUMAN_ARMATURE
