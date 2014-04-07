#ifndef _H_PUNK_UTILITY_MODEL
#define _H_PUNK_UTILITY_MODEL

#include "../config.h"
#include "../../math/math.h"
#include "../../system/system.h"
#include "../../images/images.h"
#include "../../string/string.h"
#include <map>
#include <vector>
#include "material.h"
#include "armature.h"

namespace Utility
{
	class StaticMesh;
	class SkinMesh;
	class SkinAnimation;

	typedef std::map<Core::String, Material> MaterialCollection;

	class PUNK_ENGINE_API RawScene
	{	
		MaterialCollection m_materials;
	public:
		void OpenFile(const Core::String& filename);
		StaticMesh* CookStaticMesh(const Core::String& name);
		SkinMesh* CookSkinnedMesh(const Core::String& name);
		SkinAnimation* CookSkinAnimation(const Core::String& mesh_name, unsigned anim_id);		

		Material GetMaterial(const Core::String& name) const;
		Material GetMaterial(unsigned index) const;

	private:		
	};
}


#endif