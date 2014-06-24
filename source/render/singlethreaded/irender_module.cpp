#include <core/ifactory.h>
#include <render/error/module.h>
#include <system/module.h>
#include <graphics/module.h>
#include <attributes/module.h>
#include "irender_module.h"
#include <images/module.h>
#include <system/environment.h>
#include <core/ifactory.h>
#include <graphics/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <system/module.h>
#include <core/module.h>
#include "render_cache.h"
#include "irender_processor.h"
#include "irender_observer.h"

PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	class PUNK_ENGINE_LOCAL RenderModule : public IRenderModule, public IRenderProcessor, public IRenderObserver {
	public:
		RenderModule();
		virtual ~RenderModule();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IRenderProcessor
		void SetSceneManager(SceneModule::ISceneManager* manager) override;
		void Update(float dt) override;

		// IRenderObserver
		void SetScene(SceneModule::IScene* value) override;
		void OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;
		void OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) override;
		void OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;

	private:


		void Process(Graphics::IFrame* frame, SceneModule::INode* node);

		template<class T>
		struct LightCache {
			T* m_light;
			Math::vec3 m_position;
			Math::vec3 m_direction;
			LightCache(T* light, Math::vec3 world_pos, Math::vec3 world_dir)
				: m_light{ light }
				, m_direction{ world_dir }
				, m_position{ world_pos } {}
		};

		template<class T>
		struct CameraCache {
			T* m_camera;
			Math::vec3 m_position;
			Math::vec3 m_direction;

			CameraCache(T* camera, Math::vec3 world_pos, Math::vec3 dir)
				: m_camera{ camera }
				, m_position{ world_pos }
				, m_direction{ dir }
			{}
		};

		std::atomic<std::uint32_t> m_ref_count{ 1 };
		SceneModule::ISceneManager* m_manager{ nullptr };
		Graphics::IVideoDriver* m_driver{ nullptr };
		Graphics::ILowLevelRender* m_render{ nullptr };
		Graphics::IFrameBuffer* m_frame_buffer{ nullptr };
		Graphics::IFrame* m_frame{ nullptr };
		std::vector<LightCache<Attributes::IPointLight>> m_point_lights;
		std::vector<LightCache<Attributes::IDirectionalLight>> m_dir_light;
		std::vector<LightCache<Attributes::ISpotLight>> m_spot_lights;
		CameraCache<Attributes::IPerspectiveCamera> m_perspective_camera{ nullptr, { 0, 0, 0 }, { 0, 0, -1 } };

		Core::ObjectPool<Attributes::IGeometry*, Graphics::IRenderable*> m_cooked_geometry;
		std::map<SceneModule::INode*, RenderGeoemetryCache> m_geometry_cache;
		//Graphics::ICanvasUniquePtr m_canvas{ nullptr, Core::DestroyObject };
		SceneModule::ISceneGraphUniquePtr m_scene{ nullptr, Core::DestroyObject };
		SceneModule::INodeUniquePtr m_camera_node{ nullptr, Core::DestroyObject };
		Attributes::IGeometryCookerUniquePtr m_geometry_cooker{ nullptr, Core::DestroyObject };
		Graphics::IRenderableBuilderUniquePtr m_renderable_builder{ nullptr, Core::DestroyObject };
		Graphics::ICanvasUniquePtr m_canvas{ nullptr, Core::DestroyObject };
	};

	void RenderModule::QueryInterface(const Core::Guid& type, void** object) {		
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (Core::IObject*)(IRenderProcessor*)this;
			AddRef();
			return;
		}
		else if (type == IID_IRenderProcessor) {
			*object = (IRenderProcessor*)this;
			AddRef();
			return;
		}
		else if (type == IID_IRenderObserver) {
			*object = (IRenderObserver*)this;
			AddRef();
			return;
		}
		else if (type == IID_IRenderModule) {
			*object = (IRenderModule*)this;
			AddRef();
			return;
		}
		else
			*object = nullptr;
	}

	std::uint32_t RenderModule::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t RenderModule::Release() {
		std::uint32_t v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	void RenderModule::SetSceneManager(SceneModule::ISceneManager* manager) {
		m_manager = manager;
	}

	RenderModule::RenderModule() {
		auto factory = Core::GetFactory();
        m_canvas = Core::CreateInstancePtr<Graphics::ICanvas>(Graphics::IID_ICanvas);
        m_canvas->Initialize(Graphics::CanvasDescription{});
        m_canvas->GetWindow()->Open();
        m_driver = m_canvas->GetVideoDriver();
		m_render = m_driver->GetRender();
		m_frame_buffer = Graphics::GetBackbuffer();
        m_geometry_cooker = Core::CreateInstancePtr<Attributes::IGeometryCooker>(Attributes::IID_IGeometryCooker);
        m_renderable_builder = Core::CreateInstancePtr<Graphics::IRenderableBuilder>(Graphics::IID_IRenderableBuilder);
		/*Core::GetFactory()->CreateInstance(Graphics::IID_IFrame, (void**)&m_frame);
		m_frame->SetRender(m_render);*/
	}

	RenderModule::~RenderModule() {
		m_frame->Release();		
	}

	void RenderModule::Process(Graphics::IFrame* frame, SceneModule::INode* node) {
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
				if (renderable) {
					frame->PushAllState();
					if (frame->IsEnabledSkinning())
						frame->EnableSkinning(renderable->GetVertexFormat() & (Graphics::VertexComponent::BoneID::Value() | Graphics::VertexComponent::BoneID::Value()));
					frame->Submit(renderable);
					frame->PopAllState();
				}
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
                    auto point_light = Core::QueryInterfacePtr<Attributes::IPointLight>(light, Attributes::IID_IPointLight);
					if (point_light.get()) {
						auto p = frame->GetWorldMatrix() * Math::vec3(0, 0, 0);
						m_point_lights.push_back(LightCache < Attributes::IPointLight > {point_light.get(), p, { 0, 0, 0 }});
						continue;
					}
                    auto dir_light = Core::QueryInterfacePtr<Attributes::IDirectionalLight>(light, Attributes::IID_IDirectionalLight);
					if (dir_light.get()) {
						auto p = frame->GetWorldMatrix() * Math::vec3(0, 0, 0);
						auto d = (frame->GetWorldMatrix() * Math::vec4{ dir_light->GetDirection(), 0 }).XYZ();
						m_dir_light.push_back(LightCache < Attributes::IDirectionalLight > {dir_light.get(), p, d});
						continue;
					}
				}
			}
		}
		count = node->GetAttributesCountOfType<Attributes::ICamera>();
		if (count != 0) {
			for (int i = 0; i < count; ++i) {
				auto camera = node->GetAttributeOfType<Attributes::ICamera>(i);
				if (camera) {
                    auto perspective_camera = Core::QueryInterfacePtr<Attributes::IPerspectiveCamera>(camera, Attributes::IID_IPerspectiveCamera);
					if (perspective_camera.get()) {
						auto p = frame->GetWorldMatrix() * Math::vec3(0, 0, 0);
						auto d = (frame->GetWorldMatrix() * Math::vec4{ perspective_camera->GetDirection(), 0 }).XYZ();
						m_perspective_camera.m_camera = perspective_camera.get();
						m_perspective_camera.m_position = p;
						m_perspective_camera.m_direction = d;
					}
				}
			}
		}
		for (int i = 0, max_i = (int)node->GetChildrenCount(); i < max_i; ++i) {
			Process(frame, node->GetChild(i));
		}
	}

	void RenderModule::Update(float dt) {
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
		frame->EnableTexturing(true);
		frame->EnableSkinning(true);
		frame->SetLightModel(Graphics::LightModel::PerFragmentDiffuse);
	//	frame->SetWorldMatrix(Math::CreateRotation(0, 1, 0, t));
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

		if (!m_dir_light.empty()) {
			auto light = m_dir_light[0].m_light;
			auto pos = m_dir_light[0].m_position;
			auto dir = m_dir_light[0].m_direction;
			std::vector<Graphics::Batch*> batches;
			frame->GetRender()->GetRenderQueue()->SelectBatches(batches, Graphics::SelectCriteria::SelectByLightEnabled());
			for (auto& batch : batches) {

				auto& light_state = batch->m_state->light_state->m_lights[0];
				light_state.Enable();
				light_state.SetDiffuseColor(light->GetDiffuseColor());
				light_state.SetAmbientColor({ 0.1f, 0.1f, 0.1f, 0.1f });
				light_state.SetDirection(dir);
				light_state.SetPosition(pos);
				light_state.SetType(Graphics::LightType::Direction);
				light_state.SetSpecularColor(light->GetSpecularColor());
			}
		}

		if (m_perspective_camera.m_camera) {
			std::vector<Graphics::Batch*> batches;
			frame->GetRender()->GetRenderQueue()->SelectBatches(batches, Graphics::SelectCriteria::SelectAll());
			for (auto& batch : batches) {
				batch->m_state->view_state->m_camera_position = m_perspective_camera.m_position;
				batch->m_state->view_state->m_znear = m_perspective_camera.m_camera->GetNearClipPlane();
				batch->m_state->view_state->m_zfar = m_perspective_camera.m_camera->GetFarClipPlane();
				batch->m_state->view_state->m_projection = m_perspective_camera.m_camera->GetProjectionMatrix();
				batch->m_state->view_state->m_view = Math::CreateFreeCameraMatrix(m_perspective_camera.m_position, m_perspective_camera.m_direction, m_perspective_camera.m_camera->GetUpVector());
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

	void RenderModule::SetScene(SceneModule::IScene* value) {
		value->AddRef();
		m_scene.reset(value);
	}

	void RenderModule::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {
		auto count = child->GetAttributesCountOfType<Attributes::IGeometry>();
		for (int i = 0; i < (int)count; ++i) {
			auto geom = child->GetAttributeOfType<Attributes::IGeometry>(i);
			Graphics::IRenderable* renderable = nullptr;
			if (m_cooked_geometry.HasValue(geom))
			{
				renderable = m_cooked_geometry.GetValue(geom);
				auto old = child->Get<Graphics::IRenderable>(geom->GetName());
				if (old != renderable) {
					renderable->AddRef();
					child->Set<Graphics::IRenderable>(geom->GetName(), renderable);
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
				child->Set<Graphics::IRenderable>(geom->GetName(), renderable);
			}
		}
		for (int i = 0, max_i = child->GetChildrenCount(); i < max_i; ++i) {
			OnNodeAdded(child, child->GetChild(i));
		}

		count = child->GetAttributesCountOfType<Attributes::IMaterial>();
		for (int i = 0; i < (int)count; ++i) {
			auto material = child->GetAttributeOfType<Attributes::IMaterial>(i);
			auto diffuse_slot = material->GetDiffuseTextureSlot();
			if (diffuse_slot) {
				System::Folder folder;
				folder.Open(System::Environment::Instance()->GetTextureFolder());
                ImageModule::IImageReaderUniquePtr image_reader = Core::CreateInstancePtr<ImageModule::IImageReader>(ImageModule::IID_IImageReader);
                ImageModule::IImageUniquePtr image{ image_reader->Read(diffuse_slot->GetFilename()), Core::DestroyObject };
                Graphics::ITexture2DUniquePtr texture = Core::CreateInstancePtr<Graphics::ITexture2D>(Graphics::IID_ITexture2D);
				if (texture)
					texture->Initialize(image.get(), true, m_canvas->GetVideoDriver());
				diffuse_slot->SetTexture(texture.get());
			}
		}
	}

	void RenderModule::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void RenderModule::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
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
			node->Set<Graphics::IRenderable>(geom->GetName(), renderable);
		}
	}

	void RenderModule::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {

	}

	void RenderModule::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	PUNK_REGISTER_CREATOR(IID_IRenderModule, (Core::CreateInstance<RenderModule, IRenderModule>));
}
PUNK_ENGINE_END
