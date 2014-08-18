#ifndef _H_SCENE_DATA_MODEL
#define _H_SCENE_DATA_MODEL

#include <config.h>
#include <wx/dataview.h>
#include <core/module.h>
#include <scene/module.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	class SceneDataModel : public wxDataViewModel {
	public:
		SceneDataModel(Core::Pointer<SceneModule::IScene> scene);
		unsigned int GetColumnCount() const override;
		// return type as reported by wxVariant
		wxString GetColumnType(unsigned int col) const;
		// get value into a wxVariant
		void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const override;
		virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);
		// define hierarchy
		virtual wxDataViewItem GetParent(const wxDataViewItem &item) const;
		virtual bool IsContainer(const wxDataViewItem &item) const;
		virtual unsigned int GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const;
		void SetScene(Core::Pointer<SceneModule::IScene> scene);
		Core::Pointer<SceneModule::IScene> GetScene() const;
		void RemoveAllNotifiers();

		void AddNode(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child);
		void RemoveNode(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child);
		void AddAttribute(Core::Pointer<SceneModule::INode> owner, Core::Pointer<SceneModule::IAttribute> child);
		void RemoveAttribute(Core::Pointer<SceneModule::INode> owner, Core::Pointer<SceneModule::IAttribute> child);

	private:
		Core::Pointer<SceneModule::IScene> m_scene;
	};
}
PUNK_ENGINE_END
#endif	//	_H_SCENE_DATA_MODEL