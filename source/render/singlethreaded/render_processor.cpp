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
		if (!m_ref_count.fetch_sub(1)) {
			delete this; \
		}
		return m_ref_count;
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

	void RenderProcessor::Update(int dt) {
		if (!m_manager)
			return;

		m_frame_buffer->Bind();
		m_frame_buffer->SetClearColor(0, 0, 1, 1);		
		m_frame_buffer->SetClearFlag(true, true, true);
		m_frame_buffer->Clear();
		Graphics::IFrame* frame = m_render->BeginFrame();
		frame->SetWorldMatrix(Math::CreateIdentity());
		frame->SetViewMatrix(Math::CreateIdentity());
		frame->SetProjectionMatrix(Math::CreateOrthographicProjection(0, 1024, 0, 768, -1, 1));
		frame->DrawLine(100, 100, 200, 200);
		frame->DrawLine(200, 200, 300, 100);
		frame->DrawLine(300, 100, 100, 100);
		frame->DrawQuad(400, 100, 100, 100);
		m_render->EndFrame();
		m_frame_buffer->Unbind();
		m_canvas->SwapBuffers();				
		m_canvas->GetWindow()->Update(dt);
	}

	PUNK_REGISTER_CREATOR(IID_IRenderProcessor, Core::CreateInstance<RenderProcessor>);
}
PUNK_ENGINE_END