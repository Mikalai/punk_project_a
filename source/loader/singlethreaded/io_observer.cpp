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

	Core::Pointer<Core::IObject> IoObserver::GetFileData(const Core::String& filename) {
		Core::Pointer<Core::IObject> o{ nullptr, Core::DestroyObject };
		if (!m_loaded_stuff.HasValue(filename))
		{			
			if (m_options) {
				o = ParsePunkFile(m_options->GetDataPath() + filename);
				m_loaded_stuff.AddValue(filename, o);
			}
			else {
				System::GetDefaultLogger()->Error("No options in the scene");
			}
		}
		else {
			o = m_loaded_stuff.GetValue(filename);
		}
		return o;
	}

	void IoObserver::ProcessNode(Core::Pointer<SceneModule::INode> root) {
		LOG_FUNCTION_SCOPE;
		std::stack<Core::Pointer<SceneModule::INode>> nodes;
		nodes.push(root);
		while (!nodes.empty()){
			Core::Pointer<SceneModule::INode> node = nodes.top();
			nodes.pop();

			auto count = node->GetAttributesCountOfType<Attributes::IFileStub>();
			for (auto i = 0; i < count; ++i) {
				auto stub = node->GetAttributeOfType<Attributes::IFileStub>(i);
				auto filename = stub->GetFilename();
				if (stub->IsLoaded())
					continue;
				if (stub->IsLoaded())
					continue;
				stub->SetLoading(true);
				Core::Pointer<Core::IObject> o = GetFileData(filename);	
				//	call callback if specified
				if (stub->GetCallback()) {
                    stub->GetCallback()->operator()(o);
				}

				stub->SetLoaded(true);
				{
                    auto transform = Core::QueryInterfacePtr<Attributes::ITransform>(o, Attributes::IID_ITransform);
					if (transform)
                        node->Set<Attributes::ITransform>("Transform", transform);
				}
				{
                    auto geometry = Core::QueryInterfacePtr<Attributes::IGeometry>(o, Attributes::IID_IGeometry);
					if (geometry)
                        node->Set<Attributes::IGeometry>(geometry->GetName(), geometry);
				}
				{
                    auto material = Core::QueryInterfacePtr<Attributes::IMaterial>(o, Attributes::IID_IMaterial);
					if (material) {
                        node->Set<Attributes::IMaterial>(material->GetName(), material);
					}
				}
				{
                    auto point_light = Core::QueryInterfacePtr<Attributes::ILight>(o, Attributes::IID_ILight);
					if (point_light) {
                        node->Set<Attributes::ILight>(point_light->GetName(), point_light);
					}
				}
				{
                    auto camera = Core::QueryInterfacePtr<Attributes::ICamera>(o, Attributes::IID_ICamera);
					if (camera.get())
						node->Set<Attributes::ICamera>(camera->GetName(), camera);
				}
				{
                    auto armature = Core::QueryInterfacePtr<Attributes::IArmature>(o, Attributes::IID_IArmature);
					if (armature.get()) {
						auto schema = GetFileData(armature->GetSchemaName());
						armature->SetSchema(schema);
						node->Set<Attributes::IArmature>(armature->GetName(), armature);
					}
				}				
				{
					auto options = Core::QueryInterfacePtr<Attributes::IOptions>(o, Attributes::IID_IOptions);
					if (options)
						m_options = options;
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

	void IoObserver::OnNodeAdded(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) {
		LOG_FUNCTION_SCOPE;
		ProcessNode(child);
	}

	void IoObserver::OnNodeRemoved(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) {
		LOG_FUNCTION_SCOPE;
	}

	void IoObserver::OnAttributeAdded(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) {
		LOG_FUNCTION_SCOPE;
		if (attribute->GetTypeID() == typeid(Attributes::IFileStub).hash_code()) {
			auto stub = attribute->Get<Attributes::IFileStub>();
			

			Core::Pointer<Core::IObject> o = GetFileData(stub->GetFilename());

			if (stub->GetCallback()) {
				stub->GetCallback()->operator()(o);
			}
			{
				{
                    auto geom = Core::QueryInterfacePtr<Attributes::IGeometry>(o, Attributes::IID_IGeometry);
					if (geom)
                        node->Set<Attributes::IGeometry>(geom->GetName(), geom);
				}
				{
                    auto scene = Core::QueryInterfacePtr<SceneModule::IScene>(o, SceneModule::IID_IScene);
					if (scene) {
						auto new_root = scene->GetRoot();						
						m_scene->GetRoot()->RemoveAllChildren();
						m_scene->GetRoot()->AddChild(new_root);
					}
				}
				{
                    auto material = Core::QueryInterfacePtr<Attributes::IMaterial>(o, Attributes::IID_IMaterial);
					if (material) {
                        node->Set<Attributes::IMaterial>(material->GetName(), material);
					}
				}
			}			
		}
		{
			auto options = attribute->Get<Attributes::IOptions>();
			if (options)
				m_options = options;
		}
	}

	void IoObserver::OnAttributeUpdated(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> old_attribute, Core::Pointer<SceneModule::IAttribute> new_attribute) {
		LOG_FUNCTION_SCOPE;
		OnAttributeAdded(node, new_attribute);
	}

	void IoObserver::OnAttributeRemoved(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) {
		LOG_FUNCTION_SCOPE;
	}

    PUNK_REGISTER_CREATOR(CLSID_IoObserver, (System::CreateInstance<IoObserver, IIoObserver>));
}

PUNK_ENGINE_END
