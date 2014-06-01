#include <core/ifactory.h>
#include <graphics/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <system/module.h>
#include "render_observer.h"

PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	RenderObserver::RenderObserver() {
		Core::GetFactory()->CreateInstance(Attributes::IID_IGeometryCooker, (void**)&m_geometry_cooker);
		Core::GetFactory()->CreateInstance(Graphics::IID_IRenderableBuilder, (void**)&m_renderable_builder);
	}

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
			Graphics::IRenderable* renderable = nullptr;
			if (m_cooked_geometry.HasValue(geom))
			{
				renderable = m_cooked_geometry.GetValue(geom);				
				auto old = child->Get<Graphics::IRenderable>("Renderable");
				if (old != renderable) {
					renderable->AddRef();
					child->Set<Graphics::IRenderable>("Renderable", renderable);
				}
			}
			else
			{
				Graphics::IVertexArray* vb;
				Graphics::IIndexArray* ib;
				m_geometry_cooker->Cook(geom, vb, ib);
				renderable = m_renderable_builder->ToRenderable(Graphics::PrimitiveType::TRIANGLES, vb, ib);
				delete vb;
				delete ib;
				void* v = renderable->MapVertexBuffer();
				//((Math::vec4*)v)->X() = 4;
				void* ii = renderable->MapIndexBuffer();
				renderable->UnmapVertexVuffer(v);
				renderable->UnmapIndexBuffer(ii);
				m_cooked_geometry.AddValue(geom, renderable);				
				child->Set<Graphics::IRenderable>("Renderable", renderable);
			}			
		}
		for (int i = 0, max_i = child->GetChildrenCount(); i < max_i; ++i) {
			OnNodeAdded(child, child->GetChild(i));
		}
	}

	void RenderObserver::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void RenderObserver::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		if (attribute->GetTypeID() == typeid(Attributes::IGeometry).hash_code()) {
			auto geom = attribute->Get<Attributes::IGeometry>();
			Graphics::IRenderable* renderable = nullptr;
			if (m_cooked_geometry.HasValue(geom))
			{
				renderable = m_cooked_geometry.GetValue(geom);
				renderable->AddRef();
			}
			else
			{
				Graphics::IVertexArray* vb;
				Graphics::IIndexArray* ib;
				m_geometry_cooker->Cook(geom, vb, ib);
				renderable = m_renderable_builder->ToRenderable(Graphics::PrimitiveType::TRIANGLES, vb, ib);
				m_cooked_geometry.AddValue(geom, renderable);
			}
			node->Set<Graphics::IRenderable>("Renderable", renderable);
		}
	}

	void RenderObserver::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {

	}

	void RenderObserver::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	PUNK_REGISTER_CREATOR(IID_IRenderObserver, Core::CreateInstance<RenderObserver>);
}

PUNK_ENGINE_END
