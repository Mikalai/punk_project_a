#ifndef _H_PUNK_VIRTUAL_SKINNING_TYPES
#define _H_PUNK_VIRTUAL_SKINNING_TYPES

#include <memory>
#include <map>
#include <vector>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class Bone;
    typedef Core::String BoneName;
	typedef int BoneID;		
	typedef float Weight;
	typedef std::map<BoneName, Weight> BoneWeights;
	typedef std::map<BoneName, std::shared_ptr<Bone>> BonesCollection;
	typedef std::vector<Bone*> BonesCache;
	typedef std::map<BoneName, Bone*> BonesNamedCache;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_SKINNING_TYPES
