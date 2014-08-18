#include <config.h>
#include <wx/dataview.h>
#include "scene_model.h"
#include "common.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	SceneDataModel::SceneDataModel(Core::Pointer<SceneModule::IScene> scene)
		: m_scene{ scene } {	
	}

	unsigned int SceneDataModel::GetColumnCount() const {
		return 2;
	}

	void SceneDataModel::RemoveAllNotifiers() {
		m_notifiers.Clear();
	}

	// return type as reported by wxVariant
	wxString SceneDataModel::GetColumnType(unsigned int col) const {
		return "Text";
	}

	// get value into a wxVariant
	void SceneDataModel::GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const {
		Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::IAttribute> attribute{ nullptr, Core::DestroyObject };
		if (!item.IsOk()) {
			node = m_scene->GetRoot();
		}
		else {
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
		}
		if (node) {
			variant = "Node";
		}
		else if (attribute) {
			if (col == 0) {
				variant = Common::PunkStringToWxString(attribute->GetName());
			}
			else {
				variant = "Attribute";
			}
		}
		else {
			variant = "Unknown";
		}
	}

	bool SceneDataModel::SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col) {
		Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
		if (!item.IsOk()) {
			node = m_scene->GetRoot();
		}
		else {
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
		}
		return true;
	}

	// define hierarchy
	wxDataViewItem SceneDataModel::GetParent(const wxDataViewItem &item) const {
		if (!item.IsOk())
			return wxDataViewItem{ nullptr };
		auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
		auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
		if (node) {
			return wxDataViewItem{ (void*)node->GetParent() };
		}
		auto attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
		if (attribute) {
			return wxDataViewItem{ (void*)attribute->GetOwner() };
		}
		return wxDataViewItem{ nullptr };
	}

	bool SceneDataModel::IsContainer(const wxDataViewItem &item) const {
		if (!item.IsOk()) {
			if (m_scene.get() && m_scene->GetRoot().get())
				return m_scene->GetRoot()->GetChildrenCount() != 0;
		}
		auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
		auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
		if (node) {
			return node->GetChildrenCount() != 0 || node->GetAttributesCount() != 0;
		}
		return false;
	}

	unsigned int SceneDataModel::GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const {
		if (!m_scene.get())
			return 0;
		Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
		if (!item.IsOk()) {
			node = m_scene->GetRoot();
			if (node) {
				children.push_back(wxDataViewItem{ node.get() });
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
		}

		if (node) {
			std::uint32_t count = node->GetChildrenCount();
			for (std::uint32_t i = 0, max_i = count; i < max_i; ++i) {
				children.push_back(wxDataViewItem{ (void*)node->GetChild(i).get() });
			}
			count += node->GetAttributesCount();
			for (std::uint32_t i = 0, max_i = node->GetAttributesCount(); i < max_i; ++i) {
				children.push_back(wxDataViewItem{ (void*)node->GetAttribute(i).get() });
			}
			return count;
		}
		return 0;
	}

	void SceneDataModel::SetScene(Core::Pointer<SceneModule::IScene> scene) {
		m_scene = scene;
		ItemChanged(wxDataViewItem{ nullptr });
	}

	Core::Pointer<SceneModule::IScene> SceneDataModel::GetScene() const {
		return m_scene;
	}

	void SceneDataModel::AddNode(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) {
		if (parent) {
			parent->AddChild(child);
		}
		else {
			GetScene()->SetRoot(child);
		}
		ItemAdded(wxDataViewItem{ parent.get() }, wxDataViewItem{ child.get() });
	}

	void SceneDataModel::RemoveNode(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) {
		if (GetScene()->GetRoot() == child) {
			GetScene()->SetRoot(Core::Pointer < SceneModule::INode > {nullptr, Core::DestroyObject});
		}
		else {
			parent->RemoveChild(child);
		}
		ItemDeleted(wxDataViewItem{ parent.get() }, wxDataViewItem{ child.get() });
	}

	void SceneDataModel::AddAttribute(Core::Pointer<SceneModule::INode> owner, Core::Pointer<SceneModule::IAttribute> child) {
		owner->AddAttribute(child);
		ItemAdded(wxDataViewItem{ owner.get() }, wxDataViewItem{ child.get() });
	}

	void SceneDataModel::RemoveAttribute(Core::Pointer<SceneModule::INode> owner, Core::Pointer<SceneModule::IAttribute> child) {
		if (child) {
			owner->RemoveAttribute(child);
		}
		ItemDeleted(wxDataViewItem{ owner.get() }, wxDataViewItem{ child.get() });
	}

}
PUNK_ENGINE_END
