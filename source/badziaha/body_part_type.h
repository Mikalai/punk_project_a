#ifndef _H_BODY_PART_TYPE
#define _H_BODY_PART_TYPE

#include <QtCore/qstring.h>

enum BodyPartType {
	LeftFoot,
	RightFoot,
	LeftCrus,
	RightCrus,
	LeftThigh,
	RightThigh,
	LeftPalm,
	RightPalm,
	LeftForearm,
	RightForearm,
	LeftArm,
	RightArm,
	Neck,
	Chest,
	Stomach,
	LeftCollarBone,
	RightCollarBone,
	Head,
	Pelvis,
	End
};

const QString toString(BodyPartType value);
BodyPartType fromString(const QString& value);

#endif	//	_H_BODY_PART_TYPE