#include <stack>
#include <core/ifactory.h>
#include <core/iobject.h>
#include <attributes/module.h>
#include <scene/singlethreaded/module.h>
#include <loader/parser/parse_punk_file.h>
#include "loader/error/loader_error.h"
#include "loader_cache.h"
#include "io_observer.h"
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

	IoObserver::IoObserver(){}

	IoObserver::~IoObserver() {}

	void IoObserver::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IIoObserver });
	}

	void IoObserver::ProcessNode(SceneModule::INode* root) {
		std::stack<SceneModule::INode*> nodes;
		nodes.push(root);
		while (!nodes.empty()){
			SceneModule::INode* node = nodes.top();
			nodes.pop();

			auto count = node->GetAttributesCountOfType<Attributes::IFileStub>();
			for (auto i = 0; i < count; ++i) {
				Attributes::IFileStub* stub = node->GetAttributeOfType<Attributes::IFileStub>(i);
				auto filename = stub->GetFilename();
				if (stub->IsLoaded())
					continue;
				if (stub->IsLoaded())
					continue;
				stub->SetLoading(true);
				Core::IObject* o = ParsePunkFile(m_scene->GetSourcePath() + filename);
				stub->SetLoaded(true);
				{
					Attributes::ITransform* transform = nullptr;
					o->QueryInterface(Attributes::IID_ITransform, (void**)&transform);
					if (transform)
						node->Set<Attributes::ITransform>("Transform", transform);
				}
				{
					Attributes::IGeometry* geometry = nullptr;
					o->QueryInterface(Attributes::IID_IGeometry, (void**)&geometry);
					if (geometry)
						node->Set<Attributes::IGeometry>(geometry->GetName(), geometry);
				}
				{
					Attributes::IMaterial* material = nullptr;
					o->QueryInterface(Attributes::IID_IMaterial, (void**)&material);
					if (material) {
						node->Set<Attributes::IMaterial>(material->GetName(), material);
					}
				}
				{
					Attributes::ILight* point_light = nullptr;
					o->QueryInterface(Attributes::IID_ILight, (void**)&point_light);
					if (point_light) {
						node->Set<Attributes::ILight>(point_light->GetName(), point_light);
					}
				}
				{
					Attributes::ICamera* camera = nullptr;
					o->QueryInterface(Attributes::IID_ICamera, (void**)&camera);
					if (camera)
						node->Set<Attributes::ICamera>(camera->GetName(), camera);
				}
				{
					Attributes::IArmature* armature = nullptr;
					o->QueryInterface(Attributes::IID_IArmature, (void**)&armature);
					if (armature)
						node->Set<Attributes::IArmature>(armature->GetName(), armature);
				}
			}

			for (int i = 0, max_i = (int)node->GetChildrenCount(); i < max_i; ++i) {
				nodes.push(node->GetChild(i));
			}
		}
	}

	void IoObserver::SetScene(SceneModule::IScene* value) {
		m_scene = value;
		ProcessNode(m_scene->GetRoot());
	}

	void IoObserver::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {
		ProcessNode(child);
	}

	void IoObserver::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void IoObserver::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		if (attribute->GetTypeID() == typeid(Attributes::IFileStub).hash_code()) {
			auto stub = attribute->Get<Attributes::IFileStub>();
			Core::IObjectUniquePtr o{ ParsePunkFile(stub->GetFilename()), Core::DestroyObject };
			{
				{
					Attributes::IGeometry* geom = nullptr;
					o->QueryInterface(Attributes::IID_IGeometry, (void**)&geom);
					if (geom)
						node->Set<Attributes::IGeometry>(geom->GetName(), geom);
				}
				{
					SceneModule::IScene* scene = nullptr;
					o->QueryInterface(SceneModule::IID_IScene, (void**)&scene);
					if (scene) {
						SceneModule::INode* new_root = scene->GetRoot();
						//	we will use this node from proxy scene, thus inc ref count, to protect delete when proxy scene will be deleted
						new_root->AddRef();
						m_scene->SetRoot(new_root);
						//	we don't need proxy scene
						scene->Release();
					}
				}
				{
					Attributes::IMaterial* material = nullptr;
					o->QueryInterface(Attributes::IID_IMaterial, (void**)&material);
					if (material) {
						node->Set<Attributes::IMaterial>(material->GetName(), material);
					}
				}
			}			
		}
	}

	void IoObserver::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {
		
		OnAttributeAdded(node, new_attribute);
	}

	void IoObserver::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	PUNK_REGISTER_CREATOR(IID_IIoObserver, (Core::CreateInstance<IoObserver, IIoObserver>));
}

PUNK_ENGINE_END
