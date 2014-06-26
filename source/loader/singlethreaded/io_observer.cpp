#include <stack>
#include <system/factory/module.h>
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

    IoObserver::IoObserver()
        : m_ref_count{ 0 }
    {
		LOG_FUNCTION_SCOPE;
    }

    IoObserver::~IoObserver() {
		LOG_FUNCTION_SCOPE;
    }

	void IoObserver::QueryInterface(const Core::Guid& type, void** object) {
		LOG_FUNCTION_SCOPE;
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IIoObserver });
	}

    std::uint32_t IoObserver::AddRef() {
		LOG_FUNCTION_SCOPE;
        return m_ref_count.fetch_add(1);
    }

    std::uint32_t IoObserver::Release() {
		LOG_FUNCTION_SCOPE;
        auto v = m_ref_count.fetch_sub(1) - 1;
        if (!v)
            delete this;
        return v;
    }

	void IoObserver::ProcessNode(SceneModule::INode* root) {
		LOG_FUNCTION_SCOPE;
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
                Core::Pointer<Core::IObject> o{ParsePunkFile(m_scene->GetSourcePath() + filename), Core::DestroyObject};
				
				//	call callback if specified
				if (stub->GetCallback()) {
                    (*stub->GetCallback())(o.get());
				}

				stub->SetLoaded(true);
				{
                    auto transform = Core::QueryInterfacePtr<Attributes::ITransform>(o.get(), Attributes::IID_ITransform);
					if (transform)
                        node->Set<Attributes::ITransform>("Transform", transform.get());
				}
				{
                    auto geometry = Core::QueryInterfacePtr<Attributes::IGeometry>(o.get(), Attributes::IID_IGeometry);
					if (geometry)
                        node->Set<Attributes::IGeometry>(geometry->GetName(), geometry.get());
				}
				{
                    auto material = Core::QueryInterfacePtr<Attributes::IMaterial>(o.get(), Attributes::IID_IMaterial);
					if (material) {
                        node->Set<Attributes::IMaterial>(material->GetName(), material.get());
					}
				}
				{
                    auto point_light = Core::QueryInterfacePtr<Attributes::ILight>(o.get(), Attributes::IID_ILight);
					if (point_light) {
                        node->Set<Attributes::ILight>(point_light->GetName(), point_light.get());
					}
				}
				{
                    auto camera = Core::QueryInterfacePtr<Attributes::ICamera>(o.get(), Attributes::IID_ICamera);
					if (camera.get())
						node->Set<Attributes::ICamera>(camera->GetName(), camera.get());
				}
				{
                    auto armature = Core::QueryInterfacePtr<Attributes::IArmature>(o.get(), Attributes::IID_IArmature);
					if (armature.get())
						node->Set<Attributes::IArmature>(armature->GetName(), armature.get());
				}				
			}

			for (int i = 0, max_i = (int)node->GetChildrenCount(); i < max_i; ++i) {
				nodes.push(node->GetChild(i));
			}
		}
	}

	void IoObserver::SetScene(SceneModule::IScene* value) {
		LOG_FUNCTION_SCOPE;
		m_scene = value;
		ProcessNode(m_scene->GetRoot());
	}

	void IoObserver::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {
		LOG_FUNCTION_SCOPE;
		ProcessNode(child);
	}

	void IoObserver::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {
		LOG_FUNCTION_SCOPE;
	}

	void IoObserver::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
		if (attribute->GetTypeID() == typeid(Attributes::IFileStub).hash_code()) {
			auto stub = attribute->Get<Attributes::IFileStub>();
			Core::IObjectPointer o{ ParsePunkFile(stub->GetFilename()), Core::DestroyObject };
			if (stub->GetCallback()) {
				(*stub->GetCallback())(o.get());
			}
			{
				{
                    auto geom = Core::QueryInterfacePtr<Attributes::IGeometry>(o.get(), Attributes::IID_IGeometry);
					if (geom)
                        node->Set<Attributes::IGeometry>(geom->GetName(), geom.get());
				}
				{
                    auto scene = Core::QueryInterfacePtr<SceneModule::IScene>(o.get(), SceneModule::IID_IScene);
					if (scene) {
						SceneModule::INode* new_root = scene->GetRoot();
						//	we will use this node from proxy scene, thus inc ref count, to protect delete when proxy scene will be deleted
						new_root->AddRef();
						m_scene->SetRoot(new_root);						
					}
				}
				{
                    auto material = Core::QueryInterfacePtr<Attributes::IMaterial>(o.get(), Attributes::IID_IMaterial);
					if (material) {
                        node->Set<Attributes::IMaterial>(material->GetName(), material.get());
					}
				}
			}			
		}
	}

	void IoObserver::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {
		LOG_FUNCTION_SCOPE;
		OnAttributeAdded(node, new_attribute);
	}

	void IoObserver::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
	}

    PUNK_REGISTER_CREATOR(IID_IIoObserver, (System::CreateInstance<IoObserver, IIoObserver>));
}

PUNK_ENGINE_END
