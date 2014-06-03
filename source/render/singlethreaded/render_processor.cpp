#include <attributes/module.h>
#include <core/ifactory.h>
#include <graphics/module.h>
#include <system/module.h>
#include "render_processor.h"

PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	void RenderProcessor::QueryInterface(const Core::Guid& type, void** object) {		
		Core::QueryInterface(this, type, object, { IID_IRenderProcessor, Core::IID_IObject });
	}

	std::uint32_t RenderProcessor::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t RenderProcessor::Release() {
		std::uint32_t v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this; \
		}
		return v;
	}

	void RenderProcessor::SetSceneManager(SceneModule::ISceneManager* manager) {
		m_manager = manager;
	}

	RenderProcessor::RenderProcessor() {
		auto factory = Core::GetFactory();
		Core::IObject* object;
		factory->CreateInstance(Graphics::IID_ICanvas, (void**)&object);
		object->QueryInterface(Graphics::IID_ICanvas, (void**)&m_canvas);
		object->Release();
		m_canvas->Initialize(Graphics::CanvasDescription{});
		m_canvas->GetWindow()->Open();
		m_driver = m_canvas->GetVideoDriver();
		m_render = m_driver->GetRender();
		m_frame_buffer = Graphics::GetBackbuffer();
		/*Core::GetFactory()->CreateInstance(Graphics::IID_IFrame, (void**)&m_frame);
		m_frame->SetRender(m_render);*/
	}

	RenderProcessor::~RenderProcessor() {
		m_frame->Release();
		m_canvas->Release();
	}

	void RenderProcessor::Process(Graphics::IFrame* frame, SceneModule::INode* node) {
		int count = node->GetAttributesCountOfType<Attributes::ITransform>();
		if (count != 0) {
			for (int i = 0; i < count; ++i) {
				auto transform = node->GetAttributeOfType<Attributes::ITransform>(i);
				auto matrix = transform->GetMatrix();
				frame->PushAllState();
				frame->MultWorldMatrix(matrix);
				for (int i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
					Process(frame, node->GetChild(i));
				}
				frame->PopAllState();
			}
			return;
		}
		count = node->GetAttributesCountOfType<Graphics::IRenderable>();
		if (count != 0) {
			for (int i = 0; i < count; ++i) {
				auto renderable = node->GetAttributeOfType<Graphics::IRenderable>(i);
				if (renderable)
					frame->Submit(renderable);
			}
			return;
		}
		count = node->GetAttributesCountOfType<Attributes::IMaterial>();
		if (count != 0) {
			for (int i = 0; i < count; ++i){
				auto material = node->GetAttributeOfType<Attributes::IMaterial>(i);
				if (material){
					frame->PushAllState();
					frame->SetDiffuseColor(material->GetDiffuseColor());
					frame->SetSpecularColor(material->GetSpecularColor());
					frame->SetAmbientColor(material->GetAmbient());
					if (material->GetDiffuseTextureSlot())
						frame->SetDiffuseMap(0, material->GetDiffuseTextureSlot()->GetTexture(), 0);
					if (material->GetNormalTextureSlot())
						frame->SetNormalMap(material->GetNormalTextureSlot()->GetTexture(), 1);
					if (material->GetSpecularTextureSlot())
						frame->SetSpecularMap(material->GetSpecularTextureSlot()->GetTexture(), 2);
					for (int i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
						Process(frame, node->GetChild(i));
					}
					frame->PopAllState();
				}
			}
			return;
		}
		count = node->GetAttributesCountOfType<Attributes::ILight>();
		if (count != 0) {
			for (int i = 0; i < count; ++i) {
				auto light = node->GetAttributeOfType<Attributes::ILight>(i);
				if (light) {
					Core::UniquePtr<Attributes::IPointLight> point_light{ nullptr, Core::DestroyObject };
					light->QueryInterface(Attributes::IID_IPointLight, (void**)&point_light);
					if (point_light.get()) {
						auto p = frame->GetWorldMatrix() * Math::vec3(0, 0, 0);
						m_point_lights.push_back(LightCache < Attributes::IPointLight > {point_light.get(), p});
					}
				}
			}
		}
		for (int i = 0, max_i = (int)node->GetChildrenCount(); i < max_i; ++i) {
			Process(frame, node->GetChild(i));
		}
	}

	void RenderProcessor::Update(float dt) {
		if (!m_manager)
			return;

		auto root = m_manager->GetScene()->GetRoot();		
		m_point_lights.clear();
		m_spot_lights.clear();
		m_dir_light.clear();

		//m_frame_buffer->Bind();		
		m_frame_buffer->SetViewport(0, 0, 1024, 768);
		m_frame_buffer->SetClearColor(0, 0, 1, 1);		
		m_frame_buffer->SetClearFlag(true, true, true);
		m_frame_buffer->Clear();
		Graphics::IFrame* frame = m_render->BeginFrame();
		static float t = 0;
		t += (2.0 * Math::PI / 10.0f) * (dt / 1000.0f);
		frame->PushAllState();
		frame->EnableLighting(true);
		frame->SetLightModel(Graphics::LightModel::PerFragmentDiffuse);
		frame->SetWorldMatrix(Math::CreateRotation(0, 1, 0, t));
		frame->SetViewMatrix(Math::CreateTargetCameraMatrix({ 2, 2, 2 }, { 0, 0, 0 }, { 0, 1, 0 }));
		frame->SetProjectionMatrix(Math::CreatePerspectiveProjection(Math::PI/4.0f, 1024, 768, 0.1f, 100.0f));
		frame->EnableDepthTest(true);
		Process(frame, root);

		if (!m_point_lights.empty()) {
			auto light = m_point_lights[0].m_light;
			auto pos = m_point_lights[0].m_position;
			std::vector<Graphics::Batch*> batches;
			frame->GetRender()->GetRenderQueue()->SelectBatches(batches, Graphics::SelectCriteria::SelectByLightEnabled());
			for (auto& batch : batches) {

				auto& light_state = batch->m_state->light_state->m_lights[0];
				light_state.Enable();
				light_state.SetDiffuseColor(light->GetDiffuseColor());
				light_state.SetAmbientColor({ 0.1f, 0.1f, 0.1f, 0.1f});
				light_state.SetPosition(pos);
				light_state.SetType(Graphics::LightType::Point);
				light_state.SetSpecularColor(light->GetSpecularColor());
			}
		}

		frame->PopAllState();
				
		//frame->DrawLine(100, 100, 200 * sin(t), 200);
		//frame->DrawLine(200, 200, 300, 100);
		//frame->DrawLine(300, 100, 100, 100);
		//frame->DrawQuad(400, 100, 100, 100);
		m_render->EndFrame();
		//m_frame_buffer->Unbind();
		m_canvas->GetWindow()->Update(dt);
		m_canvas->SwapBuffers();						
	}

	PUNK_REGISTER_CREATOR(IID_IRenderProcessor, Core::CreateInstance<RenderProcessor>);
}
PUNK_ENGINE_END