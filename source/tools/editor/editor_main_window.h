#ifndef _H_MODULE_MANAGER_BASE
#define _H_MODULE_MANAGER_BASE

#include <config.h>
#include <punk_engine.h>
#include "forms/forms.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	
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
		void OnViewModules(wxRibbonToolBarEvent& event);
		void OnLoadModule(wxRibbonToolBarEvent& event);
		void OnUnloadModule(wxRibbonToolBarEvent& event);
		void OnSize(wxSizeEvent& event);
		void OnToggleBottomPanel(wxRibbonToolBarEvent& event);
		void OnToggleLog(wxRibbonToolBarEvent& event);
		void OnToggleFullscreen(wxRibbonToolBarEvent& event);

	protected:
		Core::Pointer<Graphics::ICanvas> m_canvas{ nullptr, Core::DestroyObject };
	};
}
PUNK_ENGINE_END

#endif	//	_H_MODULE_MANAGER_BASE