#include <QtCore/qdebug.h>
#include "body_part_type.h"

const QString toString(BodyPartType value) {
	switch (value)
	{
	case LeftFoot:
		return "LeftFoot";
	case RightFoot:
		return "RightFoot";
	case LeftCrus:
		return "LeftCrus";
	case RightCrus:
		return "RightCrus";
	case LeftThigh:
		return "LeftThigh";
	case RightThigh:
		return "RightThigh";
	case LeftPalm:
		return "LeftPalm";
	case RightPalm:
		return "RightPalm";
	case LeftForearm:
		return "LeftForearm";
	case RightForearm:
		return "RightForearm";
	case LeftArm:
		return "LeftArm";
	case RightArm:
		return "RightArm";
	case Neck:
		return "Neck";
	case Chest:
		return "Chest";
	case Stomach:
		return "Stomach";
	case LeftCollarBone:
		return "LeftCollarBone";
	case RightCollarBone:
		return "RightCollarBone";
	case Head:
		return "Head";
	case Pelvis:
		return "Pelvis";
	}
	qDebug() << "Can't body part" << value << "to string";
	return "UNKNOWN";
}
BodyPartType fromString(const QString& value) {
	if (value == "LeftFoot")
		return LeftFoot;
	if (value == "RightFoot")
		return RightFoot;
	if (value == "LeftCrus")
		return LeftCrus;
	if (value == "RightCrus")
		return RightCrus;
	if (value == "LeftThigh")
		return LeftThigh;
	if (value == "RightThigh")
		return RightThigh;
	if (value == "LeftPalm")
		return LeftPalm;
	if (value == "RightPalm")
		return RightPalm;
	if (value == "LeftForearm")
		return LeftForearm;
	if (value == "RightForearm")
		return RightForearm;
	if (value == "LeftArm")
		return LeftArm;
	if (value == "RightArm")
		return RightArm;
	if (value == "Neck")
		return Neck;
	if (value == "Chest")
		return Chest;
	if (value == "Stomach")
		return Stomach;
	if (value == "LeftCollarBone")
		return LeftCollarBone;
	if (value == "RightCollarBone")
		return RightCollarBone;
	if (value == "Head")
		return Head;
	if (value == "Pelvis")
		return Pelvis;
	qDebug() << "Can't convert string" << value << "to body part";
	return BodyPartType::End;
}
