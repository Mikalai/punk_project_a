#include <core/ifactory.h>
#include <graphics/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <system/module.h>
#include "render_observer.h"

PUNK_ENGINE_BEGIN
namespace Render {

	RenderObserver::RenderObserver() {}
	RenderObserver::~RenderObserver() {}
	
	void RenderObserver::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IRenderObserver });
	}

	void RenderObserver::SetScene(SceneModule::IScene* value) {
		m_scene = value;
	}

	void RenderObserver::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {
		auto count = child->GetAttributesCountOfType<Attributes::IGeometry>();
		for (int i = 0; i < count; ++i) {
			auto geom = child->GetAttributeOfType<Attributes::IGeometry>(i);
			if (m_cooked_geometry.HasValue(geom))
				continue;
			Graphics::IVertexArray* vb;
			Graphics::IIndexArray* ib;
			m_geometry_cooker->Cook(geom, vb, ib);
			auto renderable = m_renderable_builder->ToRenderable(Graphics::PrimitiveType::TRIANGLES, vb, ib);
			m_cooked_geometry.AddValue(geom, renderable);
			child->Set<Graphics::IRenderable>("Renderable", renderable);
		}
	}

	void RenderObserver::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void RenderObserver::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	void RenderObserver::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {

	}

	void RenderObserver::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	PUNK_REGISTER_CREATOR(IID_IRenderObserver, Core::CreateInstance<RenderObserver>);
}

PUNK_ENGINE_END
