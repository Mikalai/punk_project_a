#ifndef _H_SCENE_TREE
#define _H_SCENE_TREE

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	class SceneTreeView : public wxDialog
	{
	public:
		SceneTreeView(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	private:
		wxDECLARE_EVENT_TABLE();
	};
}

PUNK_ENGINE_END

#endif	//	_H_SCENE_TREE