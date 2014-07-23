#include <system/factory/module.h>
#include <render/error/module.h>
#include <system/module.h>
#include <graphics/module.h>
#include "irender_module.h"
#include <images/module.h>
#include <system/environment.h>
#include <system/factory/module.h>
#include <graphics/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include <system/module.h>
#include <core/module.h>
#include "render_cache.h"
#include "irender_processor.h"
#include "irender_observer.h"
#include <math/vec4.h>
#include <attributes/module.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	template<class T>
	struct LightCache {
		Core::Pointer<T> m_light{ nullptr, Core::DestroyObject };
		Math::point3d m_position;
		Math::vec3 m_direction;
		LightCache(Core::Pointer<T> light, Math::point3d world_pos, Math::vec3 world_dir)
			: m_light{ light }
			, m_direction{ world_dir }
			, m_position{ world_pos } {}
	};

	template<class T>
	struct CameraCache {
		Core::Pointer<T> m_camera{ nullptr, Core::DestroyObject };
		Math::point3d m_position;
		Math::vec3 m_direction;

		CameraCache(Core::Pointer<T> camera, Math::point3d world_pos, Math::vec3 dir)
			: m_camera{ camera }
			, m_position{ world_pos }
			, m_direction{ dir }
		{}
	};

	class PUNK_ENGINE_LOCAL RenderModuleData {
	public:
		System::ILogger* m_log{ System::GetDefaultLogger() };
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		SceneModule::ISceneManager* m_manager{ nullptr };
		Graphics::IVideoDriver* m_driver{ nullptr };
		Graphics::ILowLevelRender* m_render{ nullptr };
		Graphics::IFrameBuffer* m_frame_buffer{ nullptr };
		Graphics::IFrame* m_frame{ nullptr };
		std::vector<LightCache<Attributes::IPointLight>> m_point_lights;
		std::vector<LightCache<Attributes::IDirectionalLight>> m_dir_light;
		std::vector<LightCache<Attributes::ISpotLight>> m_spot_lights;
		CameraCache<Attributes::IPerspectiveCamera> m_perspective_camera{ Core::Pointer < Attributes::IPerspectiveCamera > {nullptr, Core::DestroyObject}, { 0, 0, 0 }, { 0, 0, -1 } };

		Core::ObjectPool<Attributes::IGeometry*, Graphics::IRenderable> m_cooked_geometry;
		std::map<Core::Pointer<SceneModule::INode>, RenderGeoemetryCache> m_geometry_cache;
		//Graphics::ICanvasPointer m_canvas{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::IScene> m_scene{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> m_camera_node{ nullptr, Core::DestroyObject };
		Attributes::IGeometryCookerPointer m_geometry_cooker{ nullptr, Core::DestroyObject };
		Graphics::IRenderableBuilderPointer m_renderable_builder{ nullptr, Core::DestroyObject };
		Graphics::ICanvasPointer m_canvas{ nullptr, Core::DestroyObject };
	};	

	class PUNK_ENGINE_LOCAL RenderModule : 
		private RenderModuleData, 
		public IRenderModule, 
		public IRenderProcessor, 
		public IRenderObserver {
	public:
		
		RenderModule() 
		{
			LOG_FUNCTION_SCOPE;			
			m_canvas = System::CreateInstancePtr<Graphics::ICanvas>(
				Graphics::CLSID_Canvas, Graphics::IID_ICanvas);
			m_canvas->Initialize(Graphics::CanvasDescription{});
			m_canvas->GetWindow()->SubscribeWindowDestroyEvent(new Core::Action<RenderModule, void>(this, &RenderModule::OnWindowClose));
			m_canvas->GetWindow()->Open();
			m_driver = m_canvas->GetVideoDriver();
			m_render = m_driver->GetRender();
			m_frame_buffer = Graphics::GetBackbuffer();
			m_frame_buffer->SetViewport(0, 0, m_canvas->GetWindow()->GetWidth(), m_canvas->GetWindow()->GetHeight());
			m_canvas->GetWindow()->SubscribeResizeEvent(new Core::Action<RenderModule, const System::WindowResizeEvent&>(this, &RenderModule::OnWindowResized));
			m_canvas->GetWindow()->SubscribeMouseMoveEvent(new Core::Action<RenderModule, const System::MouseEvent&>(this, &RenderModule::OnMouseMove));
			m_geometry_cooker = System::CreateInstancePtr<Attributes::IGeometryCooker>(
				Attributes::CLSID_GeometryCooker, Attributes::IID_IGeometryCooker);
			m_renderable_builder = System::CreateInstancePtr<Graphics::IRenderableBuilder>(
				Graphics::CLSID_RenderableBuilder, Graphics::IID_IRenderableBuilder);
		}
		
		~RenderModule() {
			LOG_FUNCTION_SCOPE;
			m_frame->Release();
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			LOG_FUNCTION_SCOPE;
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

		std::uint32_t AddRef() override {
			LOG_FUNCTION_SCOPE;
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t Release() override {
			LOG_FUNCTION_SCOPE;
			std::uint32_t v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}


		//	IRenderProcessor		
		void Terminate() {

		}

		void SetSceneManager(SceneModule::ISceneManager* manager) override {
			LOG_FUNCTION_SCOPE;
			m_manager = manager;
			auto scene = m_manager->GetScene();
			if (scene) {
				auto root = scene->GetRoot();
				if (root)
					root->Set<Graphics::ICanvas>(L"Canvas", m_canvas);
			}
		}

		void Update(float dt) override {
			LOG_FUNCTION_SCOPE;
			if (!m_manager)
				return;

			auto root = m_manager->GetScene()->GetRoot();
			m_point_lights.clear();
			m_spot_lights.clear();
			m_dir_light.clear();

			//m_frame_buffer->Bind();				
			m_frame_buffer->SetClearColor(0.5, 0.8, 0.6, 1);
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
			frame->SetViewMatrix(Math::mat4::CreateViewMatrix({ 2, 2, 2 }, Math::point3d{ 0, 0, 0 }, { 0, 1, 0 }));
			frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, 1024, 768, 0.1f, 100.0f));
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
					light_state.SetAmbientColor({ 0.1f, 0.1f, 0.1f, 0.1f });
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
					batch->m_state->view_state->m_view = Math::mat4::CreateViewMatrix(m_perspective_camera.m_position, m_perspective_camera.m_direction, m_perspective_camera.m_camera->GetUpVector());
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

		// IRenderObserver
		void SetScene(SceneModule::IScene* value) override {
			LOG_FUNCTION_SCOPE;
			value->AddRef();
			m_scene.reset(value);
			if (!m_scene->GetRoot()->Get<Graphics::ICanvas>(L"Canvas"))
				m_scene->GetRoot()->Set<Graphics::ICanvas>(L"Canvas", m_canvas);
		}

		void OnNodeAdded(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override {
			LOG_FUNCTION_SCOPE;
			if (!parent) {
				if (!child->Get<Graphics::ICanvas>(L"Canvas"))
					child->Set<Graphics::ICanvas>(L"Canvas", m_canvas);
			}
			auto count = child->GetAttributesCountOfType<Attributes::IGeometry>();
			for (int i = 0; i < (int)count; ++i) {
				auto geom = child->GetAttributeOfType<Attributes::IGeometry>(i);
				Core::Pointer<Graphics::IRenderable> renderable{ nullptr, Core::DestroyObject };
				if (m_cooked_geometry.HasValue(geom.get()))
				{
					renderable = m_cooked_geometry.GetValue(geom.get());
					auto old = child->Get<Graphics::IRenderable>(geom->GetName());
					if (old != renderable) {
						renderable->AddRef();
						child->Set<Graphics::IRenderable>(geom->GetName(), renderable);
					}
				}
				else
				{
					Core::Pointer<Graphics::IVertexArray> vb{ nullptr, Core::DestroyObject };
					Core::Pointer<Graphics::IIndexArray> ib{ nullptr, Core::DestroyObject };
					m_geometry_cooker->Cook(geom, vb, ib);
					renderable = m_renderable_builder->ToRenderable(Graphics::PrimitiveType::TRIANGLES, vb, ib);
					m_cooked_geometry.AddValue(geom.get(), renderable);
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
					ImageModule::IImageReaderPointer image_reader = System::CreateInstancePtr<ImageModule::IImageReader>(
						ImageModule::CLSID_ImageReader, ImageModule::IID_IImageReader);

					ImageModule::IImagePointer image{ image_reader->Read(diffuse_slot->GetFilename()), Core::DestroyObject };
					Graphics::ITexture2DPointer texture = System::CreateInstancePtr<Graphics::ITexture2D>(
						Graphics::CLSID_Texture2D, Graphics::IID_ITexture2D);
					if (texture)
						texture->Initialize(image.get(), true, m_canvas->GetVideoDriver());
					diffuse_slot->SetTexture(texture.get());
				}
			}
		}
		
		void OnNodeRemoved(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override {
			LOG_FUNCTION_SCOPE;
		}
		
		void OnAttributeUpdated (
			Core::Pointer<SceneModule::INode> node, 
			Core::Pointer<SceneModule::IAttribute> old_attribute, 
			Core::Pointer<SceneModule::IAttribute> new_attribute) override {
			LOG_FUNCTION_SCOPE;
		}

		void OnAttributeRemoved(
			Core::Pointer<SceneModule::INode> node, 
			Core::Pointer<SceneModule::IAttribute> attribute) override {
			LOG_FUNCTION_SCOPE;
		}

		void OnAttributeAdded(
			Core::Pointer<SceneModule::INode> node, 
			Core::Pointer<SceneModule::IAttribute> attribute) override {
			LOG_FUNCTION_SCOPE;
			if (attribute->GetTypeID() == typeid(Attributes::IGeometry).hash_code()) {
				auto geom = attribute->Get<Attributes::IGeometry>();
				Core::Pointer<Graphics::IRenderable> renderable{ nullptr, Core::DestroyObject };
				if (m_cooked_geometry.HasValue(geom.get()))
				{
					renderable = m_cooked_geometry.GetValue(geom.get());
				}
				else
				{
					Core::Pointer<Graphics::IVertexArray> vb{ nullptr, Core::DestroyObject };
					Core::Pointer<Graphics::IIndexArray> ib{ nullptr, Core::DestroyObject };
					m_geometry_cooker->Cook(geom, vb, ib);
					renderable = m_renderable_builder->ToRenderable(Graphics::PrimitiveType::TRIANGLES, vb, ib);
					m_cooked_geometry.AddValue(geom.get(), renderable);
				}
				node->Set<Graphics::IRenderable>(geom->GetName(), renderable);
			}
		}

	private:

		bool Process2dSelection(Core::Pointer<SceneModule::INode> parent, Math::vec2 parent_pos) {
			//auto count = parent->GetAttributesCountOfType<Attributes::IMouseSelectable2D>();
			//for (int i = 0; i < count; ++i) {
			//	auto selectable = parent->GetAttributeOfType<Attributes::IMouseSelectable2D>(i);
			//	auto pos = selectable->GetLocalTopLeftPosition();
			//	if (pos.x >= 0
			//		&& pos.y >= 0
			//		&& pos <= selectable->GetWidth()
			//		&& pos <= selectable->GetHeight()) {
			//		bool flag = false;
			//		for (std::uint32_t j = 0, max_j = parent->GetChildrenCount(); ++j) {
			//			flag = Process2dSelection(parent->GetChild(j), pos);
			//			if (flag)
			//				break;
			//		}
			//		if (!flag) {

			//		}
			//	}
			//}
		}		
		
		/*
		*	Process
		*/
		void Process(Graphics::IFrame* frame, Core::Pointer<SceneModule::INode> node) {
			LOG_FUNCTION_SCOPE;
			int count = node->GetAttributesCountOfType<Attributes::ITransform>();
			if (count != 0) {
				for (int i = 0; i < count; ++i) {
					auto transform = node->GetAttributeOfType<Attributes::ITransform>(i);
					auto matrix = transform->GetMatrix();
					frame->PushAllState();
					frame->MultWorldMatrix(matrix);
					frame->SetLineWidth(1);
					//frame->DrawAxis(2);
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
						if (frame->IsEnabledSkinning())
							for (int j = 0; j < Graphics::BaseState::MAX_BONES; ++j)
								frame->SetBoneMatrix(j, frame->GetLastLocalMatrix().Inversed() * frame->GetBoneMatrix(j) * frame->GetLastLocalMatrix());
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
							auto p = frame->GetWorldMatrix() * Math::point3d(0, 0, 0);
							m_point_lights.push_back(LightCache < Attributes::IPointLight > {point_light, p, { 0, 0, 0 }});
							continue;
						}
						auto dir_light = Core::QueryInterfacePtr<Attributes::IDirectionalLight>(light, Attributes::IID_IDirectionalLight);
						if (dir_light.get()) {
							auto p = frame->GetWorldMatrix() * Math::point3d(0, 0, 0);
							auto d = (frame->GetWorldMatrix() * Math::vec4{ dir_light->GetDirection(), 0 }).XYZ();
							m_dir_light.push_back(LightCache < Attributes::IDirectionalLight > {dir_light, p, d});
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
							auto p = frame->GetWorldMatrix() * Math::point3d(0, 0, 0);
							auto d = (frame->GetWorldMatrix() * Math::vec4{ perspective_camera->GetDirection(), 0 }).XYZ();
							m_perspective_camera.m_camera = perspective_camera;
							m_perspective_camera.m_position = p;
							m_perspective_camera.m_direction = d;
						}
					}
				}
			}
			count = node->GetAttributesCountOfType<Attributes::IArmature>();
			if (count != 0) {
				for (int i = 0; i < count; ++i) {
					auto armature = node->GetAttributeOfType<Attributes::IArmature>(i);
					if (armature) {
						frame->PushAllState();
						for (int i = 0; i < armature->GetSchema()->GetBonesCount(); ++i) {
							frame->PushAllState();
							frame->MultWorldMatrix(armature->GetBoneLocalMatrix(i));
							frame->DrawAxis(2);
							frame->PopAllState();
						}
						frame->EnableSkinning(true);
						for (int i = 0; i < armature->GetSchema()->GetBonesCount(); ++i) {
							frame->SetBoneMatrix(i, armature->GetBoneGlobalMatrix(i));
						}
						for (int i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
							Process(frame, node->GetChild(i));
						}
						frame->PopAllState();
						return;
					}
				}
			}
			for (int i = 0, max_i = (int)node->GetChildrenCount(); i < max_i; ++i) {
				Process(frame, node->GetChild(i));
			}
		}		

		void OnMouseMove(const System::MouseEvent& event) {
			m_log->Debug("RenderModule: " + event.ToString());
			/*std::stack<Core::Pointer<SceneModule::INode>> nodes;
			std::stack<Math::vec2> positions;
			nodes.push(m_scene->GetRoot());
			positions.push({ event.x, event.y });
			while (!nodes.empty()) {
			auto node = nodes.top();
			nodes.pop();
			auto pos_in_parent = positions.top();
			positions.pop();
			int count = node->GetAttributesCountOfType<Attributes::IMouseSelectable2D>();
			for (int i = 0; i < count; ++i) {
			auto selectable = node->GetAttributeOfType<Attributes::IMouseSelectable2D>(i);
			pos_in_parent -= selectable->GetLocalTopLeftPosition();
			if (pos_in_parent.x >= 0
			&& pos_in_parent.y >= 0
			&& pos_in_parent <= selectable->GetWidth()
			&& pos_in_parent <= selectable->GetHeight()) {

			selectable->EmitMouseMoveEvent(pos_in_parent.x, pos_in_parent.y);
			}
			}
			}*/
		}

		void OnWindowResized(const System::WindowResizeEvent& event) {
			m_frame_buffer->SetViewport(0, 0, event.width, event.height);
		}

		/*
		*	OnWindowClose
		*/
		void OnWindowClose() {
			m_manager->Terminate();
		}
	};	

    PUNK_REGISTER_CREATOR(CLSID_RenderModule, (System::CreateInstance<RenderModule, IRenderModule>));
}
PUNK_ENGINE_END
