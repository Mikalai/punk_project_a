#ifndef _H_ACTION
#define _H_ACTION

#include <config.h>
#include "action_manager.h"
#include <scene/module.h>
#include "scene_model.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	class EditorMainWindow;

	class CreateSceneAction : public ActionBase {
	public:
		CreateSceneAction(EditorMainWindow* panel, const Core::String& name);
		virtual ~CreateSceneAction();
		void Do() override;
		void Undo() override;
		void Redo() override;
	private:
		EditorMainWindow* m_panel;
		Core::String m_name;
		SceneDataModel* m_scene_model{ nullptr };
	};

	class DeleteSceneAction : public ActionBase {
	public:
		DeleteSceneAction(EditorMainWindow* panel);
		virtual ~DeleteSceneAction();

		void Do() override;
		void Undo() override;
		void Redo() override;

	private:
		EditorMainWindow* m_panel;
		SceneDataModel* m_scene_model;		
	};

	class CreateNodeAction : public ActionBase {
	public:
		CreateNodeAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> parent);
		virtual ~CreateNodeAction();

		void Do() override;
		void Undo() override;
		void Redo() override;
	private:
		EditorMainWindow* m_panel;
		SceneDataModel* m_scene_model;
		Core::Pointer<SceneModule::INode> m_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> m_parent{ nullptr, Core::DestroyObject };
		bool m_scene_root{ false };
	};

	class DeleteNodeAction : public ActionBase {
	public:
		DeleteNodeAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> node);
		virtual ~DeleteNodeAction();

		void Do() override;
		void Undo() override;
		void Redo() override;

	private:
		EditorMainWindow* m_panel;
		SceneDataModel* m_scene_model;
		Core::Pointer<SceneModule::INode> m_parent{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> m_node{ nullptr, Core::DestroyObject };
	};

	class CreateAttributeAction : public ActionBase {
	public:
		CreateAttributeAction(EditorMainWindow* panel, Core::Pointer<SceneModule::INode> parent);
		virtual ~CreateAttributeAction();

		void Do() override;
		void Undo() override;
		void Redo() override;
	private:
		EditorMainWindow* m_panel;
		SceneDataModel* m_scene_model;
		Core::Pointer<SceneModule::IAttribute> m_attribute{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> m_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> m_parent{ nullptr, Core::DestroyObject };
		bool m_scene_root{ false };
	};
}
PUNK_ENGINE_END

#endif	//	_H_ACTION