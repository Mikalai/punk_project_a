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
				Core::IObject* o = ParsePunkFile(filename);

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
			Core::IObject* o = ParsePunkFile(stub->GetFilename());
			{
				Attributes::IGeometry* geom = nullptr;
				o->QueryInterface(Attributes::IID_IGeometry, (void**)geom);
				if (geom)
					node->Set<Attributes::IGeometry>("Geometry", geom);
			}			
		}
	}

	void IoObserver::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {
		OnAttributeAdded(node, new_attribute);
	}

	void IoObserver::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	PUNK_REGISTER_CREATOR(IID_IIoObserver, Core::CreateInstance<IoObserver>);
}

PUNK_ENGINE_END
