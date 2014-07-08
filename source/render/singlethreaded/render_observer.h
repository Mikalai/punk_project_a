//#ifndef _H_PUNK_RENDER_PROCESSOR
//#define _H_PUNK_RENDER_PROCESSOR
//
//#include <config.h>
//#include <core/module.h>
//#include <string/module.h>
//#include <scene/module.h>
//#include <graphics/module.h>
//#include "irender_observer.h"
//#include "render_cache.h"
//
//PUNK_ENGINE_BEGIN
//namespace LowLevelRender {
//
//	class PUNK_ENGINE_LOCAL RenderObserver : public IRenderObserver {
//	public:
//		RenderObserver();
//		virtual ~RenderObserver();
//		void QueryInterface(const Core::Guid& type, void** object) override;
//		void SetScene(SceneModule::IScene* value) override;
//		void OnNodeAdded(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override;
//		void OnNodeRemoved(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override;
//		void OnAttributeAdded(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) override;
//		void OnAttributeUpdated(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> old_attribute, Core::Pointer<SceneModule::IAttribute> new_attribute) override;
//		void OnAttributeRemoved(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) override;
//	
//	private:
//		Core::ObjectPool<Attributes::IGeometry*, Graphics::IRenderable*> m_cooked_geometry;
//		std::map<Core::Pointer<SceneModule::INode>, RenderGeoemetryCache> m_geometry_cache;
//		//Graphics::ICanvasPointer m_canvas{ nullptr, Core::DestroyObject };
//		SceneModule::IScene* m_scene{ nullptr };
//		Core::Pointer<SceneModule::INode> m_camera_node{ nullptr };
//		Attributes::IGeometryCooker* m_geometry_cooker{ nullptr };
//		Graphics::IRenderableBuilder* m_renderable_builder{ nullptr };
//		PUNK_OBJECT_DEFAULT_IMPL(RenderObserver);
//	};
//
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_RENDER_PROCESSOR