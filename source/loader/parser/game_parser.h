#ifndef _H_PUNK_SCENE_LOADER
#define _H_PUNK_SCENE_LOADER

#include "../config.h"
#include <vector>
#include "intersection.h"
#include "../skinning/armature.h"
#include "../system/object.h"

namespace Math
{
	class OctTree;
	template<class T> class Vector3;
}

namespace System
{
	class string;
}

namespace Attributes
{
	class StaticMesh;
	class Entity;
	class Bone;
	class Animation;
	class Armature;

	////	used to iterate through all objects
	//class SceneObjectIterator
	//{
	//	struct SceneObjectIteratorImpl;
	//	std::auto_ptr<SceneObjectIteratorImpl> m_impl;
	//public:				
	//	SceneObjectIterator(Scene* scene);
	//	~SceneObjectIterator(Scene* scene);
	//	Entity* operator * ();
	//	Entity* operator -> ();
	//};

	//extern SceneObjectIterator* operator ++ (int i, SceneObjectIterator&);

	//class PUNK_ENGINE_API Scene : public Core::IObject
	//{
	//	struct SceneImpl;
	//	std::auto_ptr<SceneImpl> impl_scene;
	//public:
	//	Scene();
	//	Scene(const Scene& scene);
	//	Scene& operator = (const Scene& scene);
	//	~Scene();

	//	unsigned GetObjectsCount() const;
	//	const Core::String GetObjectName(int index) const;

	//	void Load(Core::Buffer* buffer);
	//	bool Save(std::ostream& stream);
	//	bool Load(const Core::String& filename);
	//	//Math::OctTree& GetOctTree();
	//	bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res);
	//	StaticMesh* CookStaticMesh(const Core::String& name) const;
	//	StaticMesh* CookSkinnedMesh(const Core::String& name) const;
	//	Armature* GetArmature(const Core::String& name);
	//	int GetArmatureCount() const;
	//	const Core::String GetArmatureName(int index) const;

	//	Entity* FindObjectByName(const Core::String& name);
	//	const Entity* FindObjectByName(const Core::String& name) const;
	//	Bone* FindBoneByName(const Core::String& name);
	//	const Bone* FindBoneByName(const Core::String& name) const;

	//	Animation* FindAnimationByName(const Core::String& name);
	//	const Animation* FindAnimationByName(const Core::String& name) const;

	//	void PrintDebug();	
	//};


};

#endif