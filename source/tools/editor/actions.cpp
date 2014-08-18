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
		m_scene_model->AddNode(m_parent, m_node);
	}

	void CreateNodeAction::Undo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		m_scene_model->RemoveNode(m_parent, m_node);
	}

	void CreateNodeAction::Redo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		m_scene_model->AddNode(m_parent, m_node);
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
			m_scene_model->AddAttribute(m_parent, m_attribute);			
		}		
	}

	void CreateAttributeAction::Undo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		m_scene_model->RemoveAttribute(m_parent, m_attribute);
	}

	void CreateAttributeAction::Redo() {
		if (!m_scene_model) {
			System::GetDefaultLogger()->Error("Scene model is not specified. Can't create node");
			return;
		}
		m_scene_model->AddAttribute(m_parent, m_attribute);
	}

	DragItemAction::DragItemAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> src, Core::Pointer<SceneModule::INode> dst, Core::Pointer<SceneModule::INode> drag) 
		: m_panel{ panel }
		, m_source{ src }
		, m_destination{ dst }
		, m_dragged_node{ drag } {
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model)
			System::GetDefaultLogger()->Error("Scene model is null");
		else
			m_scene_model->IncRef();
	}

	DragItemAction::DragItemAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> src, Core::Pointer<SceneModule::INode> dst, Core::Pointer<SceneModule::IAttribute> drag) 
		: m_panel{ panel }
		, m_source{ src }
		, m_destination{ dst }
		, m_dragged_attribute{ drag } {
		if (!m_panel)
			System::GetDefaultLogger()->Error("Panel is null");
		m_scene_model = m_panel->GetCurrentSceneModel();
		if (!m_scene_model)
			System::GetDefaultLogger()->Error("Scene model is null");
		else
			m_scene_model->IncRef();
	}

	DragItemAction::~DragItemAction() {
		if (m_scene_model)
			m_scene_model->DecRef();
	}

	void DragItemAction::Do() {
		if (m_dragged_node) {
			m_scene_model->RemoveNode(m_source, m_dragged_node);
			m_scene_model->AddNode(m_destination, m_dragged_node);
		}
		if (m_dragged_attribute) {
			m_scene_model->RemoveAttribute(m_source, m_dragged_attribute);
			m_scene_model->AddAttribute(m_destination, m_dragged_attribute);
		}
	}

	void DragItemAction::Undo() {
		if (m_dragged_node) {
			m_scene_model->RemoveNode(m_destination, m_dragged_node);
			m_scene_model->AddNode(m_source, m_dragged_node);
		}
		if (m_dragged_attribute) {
			m_scene_model->RemoveAttribute(m_destination, m_dragged_attribute);
			m_scene_model->AddAttribute(m_source, m_dragged_attribute);
		}
	}
	
	void DragItemAction::Redo() {
		if (m_dragged_node) {
			m_scene_model->RemoveNode(m_source, m_dragged_node);
			m_scene_model->AddNode(m_destination, m_dragged_node);
		}
		if (m_dragged_attribute) {
			m_scene_model->RemoveAttribute(m_source, m_dragged_attribute);
			m_scene_model->AddAttribute(m_destination, m_dragged_attribute);
		}
	}
}
PUNK_ENGINE_END
