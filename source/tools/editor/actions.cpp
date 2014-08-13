#include "editor_main_window.h"
#include "forms/attribute_dialog_impl.h"
#include "actions.h"
#include "common.h"
#include "actions.h"
#include "scene_model.h"
#include <system/factory/module.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	void AddSceneModel(EditorMainWindow* panel, SceneDataModel* model) {
		auto combobox = panel->GetSceneCombobox();
		if (!combobox)
			return;
		auto name = Common::PunkStringToWxString(model->GetScene()->GetName());
		combobox->Append(name, (void*)model);	
		combobox->Enable();
	}

	void RemoveSceneModel(EditorMainWindow* panel, SceneDataModel* model) {
		auto combobox = panel->GetSceneCombobox();
		for (auto i = 0; i < combobox->GetCount(); ++i) {
			auto tmp = (SceneDataModel*)combobox->GetClientData(i);
			if (tmp == model) {
				combobox->Delete(i);
				break;
			}
		}
		if (!combobox->GetCount())
			combobox->Disable();
	}

	CreateSceneAction::CreateSceneAction(EditorMainWindow* panel, const Core::String& name)
		: m_name{ name }
		, m_panel{ panel } {
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model)
			System::GetDefaultLogger()->Error("Scene model is null");
		else
			m_scene_model->IncRef();
	}

	CreateSceneAction::~CreateSceneAction() {
		if (m_scene_model) {
			m_scene_model->DecRef();
			m_scene_model = nullptr;
		}
	}

	void CreateSceneAction::Do() {
		auto scene = System::CreateInstancePtr<SceneModule::IScene>(SceneModule::CLSID_Scene, SceneModule::IID_IScene);
		m_scene_model = new SceneDataModel{ scene };

		scene->SetName(m_name);
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		scene_manager->AddScene(scene);	
		AddSceneModel(m_panel, m_scene_model);
		//m_panel->SetCurrentSceneModel(m_scene_model);
		//UpdateSceneComboBox(m_panel);
	}

	void CreateSceneAction::Undo() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		auto index = scene_manager->GetSceneIndex(m_scene_model->GetScene());
		scene_manager->RemoveScene(index);
		m_panel->SetCurrentSceneModel(nullptr);		
		RemoveSceneModel(m_panel, m_scene_model);
	}

	void CreateSceneAction::Redo() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		scene_manager->AddScene(m_scene_model->GetScene());
		//m_panel->SetCurrentSceneModel(m_scene_model);
		AddSceneModel(m_panel, m_scene_model);
	}

	DeleteSceneAction::DeleteSceneAction(EditorMainWindow* panel)
		: m_panel{ panel } {
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model)
			System::GetDefaultLogger()->Error("Scene model is null");
		else
			m_scene_model->IncRef();
	}

	DeleteSceneAction::~DeleteSceneAction() {
		if (m_scene_model) {
			m_scene_model->DecRef();
		}
	}

	void DeleteSceneAction::Do() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		auto index = scene_manager->GetSceneIndex(m_scene_model->GetScene());
		scene_manager->RemoveScene(index);
		m_panel->SetCurrentSceneModel(nullptr);
		RemoveSceneModel(m_panel, m_scene_model);
	}

	void DeleteSceneAction::Undo() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		scene_manager->AddScene(m_scene_model->GetScene());
		//m_panel->SetCurrentSceneModel(m_scene_model);
		AddSceneModel(m_panel, m_scene_model);
	}

	void DeleteSceneAction::Redo() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		auto index = scene_manager->GetSceneIndex(m_scene_model->GetScene());
		scene_manager->RemoveScene(index);
		m_panel->SetCurrentSceneModel(nullptr);
		RemoveSceneModel(m_panel, m_scene_model);
	}

	CreateNodeAction::CreateNodeAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> parent)
		: m_panel{ panel }
		, m_parent{ parent }		
	{		
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model) 
			System::GetDefaultLogger()->Error("Scene model is null");
		else 
			m_scene_model->IncRef();
		if (!m_parent) {
			m_parent = m_scene_model->GetScene()->GetRoot();
		}
	}

	CreateNodeAction::~CreateNodeAction() {
		if (m_scene_model)
			m_scene_model->DecRef();
	}

	void CreateNodeAction::Do() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		m_node = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);		
		if (m_parent) {
			m_parent->AddChild(m_node);
			m_scene_root = false;
		}
		else {			
			m_scene_model->GetScene()->SetRoot(m_node);
			m_scene_root = true;
		}		
		m_scene_model->ItemAdded(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_node.get() });
	}

	void CreateNodeAction::Undo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		if (m_scene_root)
			m_scene_model->GetScene()->SetRoot(Core::Pointer < SceneModule::INode > {nullptr, Core::DestroyObject});
		else 
			m_parent->RemoveChild(m_node);
		m_scene_model->ItemDeleted(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_node.get() });
	}

	void CreateNodeAction::Redo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		if (m_scene_root)
			m_scene_model->GetScene()->SetRoot(m_node);
		else
			m_parent->AddChild(m_node);
		//m_panel->SetCurrentSceneModel(m_scene_model);
		m_scene_model->ItemAdded(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_node.get() });
	}

	CreateAttributeAction::CreateAttributeAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> parent)
		: m_panel{ panel }
		, m_parent{ parent }
	{
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model)
			System::GetDefaultLogger()->Error("Scene model is null");
		else
			m_scene_model->IncRef();
		if (!m_parent) {
			m_parent = m_scene_model->GetScene()->GetRoot();
		}
	}

	CreateAttributeAction::~CreateAttributeAction() {
		if (m_scene_model)
			m_scene_model->DecRef();
	}

	void CreateAttributeAction::Do() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		AttributeDialogImpl dlg(m_panel);
		if (dlg.ShowModal() == wxID_OK) {
			m_attribute = System::CreateInstancePtr<SceneModule::IAttribute>(SceneModule::CLSID_Attribute, SceneModule::IID_IAttribute);
			if (m_attribute) {
				m_attribute->Initialize(dlg.GetObjectName(), dlg.GetObject());
			}
			m_parent->AddAttribute(m_attribute);
			m_scene_model->ItemAdded(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_attribute.get() });
		}		
	}

	void CreateAttributeAction::Undo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		if (m_attribute) {
			m_parent->RemoveAttribute(m_attribute);
		}
		m_scene_model->ItemDeleted(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_attribute.get() });
	}

	void CreateAttributeAction::Redo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		if (m_attribute) {
			m_parent->AddAttribute(m_attribute);
		}
		//m_panel->SetCurrentSceneModel(m_scene_model);
		m_scene_model->ItemAdded(wxDataViewItem{ m_parent.get() }, wxDataViewItem{ m_attribute.get() });
	}
}
PUNK_ENGINE_END
