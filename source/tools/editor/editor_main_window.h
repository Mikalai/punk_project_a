#ifndef _H_MODULE_MANAGER_BASE
#define _H_MODULE_MANAGER_BASE

#include <config.h>
#include <punk_engine.h>
#include "forms/forms.h"

PUNK_ENGINE_BEGIN
namespace Tools {

#define ID_SCENE_MENU_ADD_ATTRIBUTE 10000

	class EditorMainWindow : public EditorMainWindowBase, public System::ILogConsumer {
	public:
		using EditorMainWindowBase::EditorMainWindowBase;
		
		EditorMainWindow(wxWindow* parent);

		//	ILogConsumer
		void Write(const Core::String& time, const Core::String& level, const Core::String &message) override;

	protected:
		void OnActivate(wxActivateEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnIdle(wxIdleEvent& event);
		void OnToggleBottomPanel(wxRibbonToolBarEvent& event);
		void OnToggleLog(wxRibbonToolBarEvent& event);
		void OnToggleFullscreen(wxRibbonToolBarEvent& event);
		void OnViewModules(wxRibbonToolBarEvent& event);
		void OnLoadModule(wxRibbonToolBarEvent& event);
		void OnUnloadModule(wxRibbonToolBarEvent& event);
		void OnSceneCreate(wxRibbonToolBarEvent& event);
		void OnSceneDelete(wxRibbonToolBarEvent& event);
		void OnNodeCreate(wxRibbonToolBarEvent& event);
		void OnNodeDelete(wxRibbonToolBarEvent& event);
		void OnUpdateScenePanel(wxUpdateUIEvent& event);
		void OnSceneChanged(wxCommandEvent& event);
		void OnSize(wxSizeEvent& event);
		void OnUndo(wxRibbonToolBarEvent& event);
		void OnRedo(wxRibbonToolBarEvent& event);
		void OnSwitchDetailedGraph(wxCommandEvent& event);
		void OnSwitchObjectsGraph(wxCommandEvent& event);
		void OnSceneGraphItemActivated(wxDataViewEvent& event);
		void OnSceneGraphItemChanged(wxDataViewEvent& event);
		void OnSceneLoad(wxRibbonToolBarEvent& event);
		void OnSceneSave(wxRibbonToolBarEvent& event);
		void OnSceneContextMenu(wxDataViewEvent& event);
		void OnScenePopUpClick(wxCommandEvent& event);
	public:
		void UpdateScenePanel();
		void UpdateSceneGraph();
	protected:
		Core::Pointer<Graphics::ICanvas> m_canvas{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::IScene> m_current_scene{ nullptr, Core::DestroyObject};
		Core::Pointer<SceneModule::INode> m_current_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::IAttribute> m_current_attribute{ nullptr, Core::DestroyObject };
	};
}
PUNK_ENGINE_END

#endif	//	_H_MODULE_MANAGER_BASE