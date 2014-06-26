#include <system/factory/module.h>
#include <application/error/module.h>
#include <system/module.h>
#include <render/module.h>
#include <loader/module.h>
#include <scene/module.h>
#include <animator/module.h>
#include <config.h>
#include <system/logger/module.h>
#include <system/factory/module.h>
#include "iapplication.h"

PUNK_ENGINE_BEGIN
namespace Runtime {

    class PUNK_ENGINE_LOCAL Application : public IApplication {
    public:

        Application();
        virtual ~Application();
        void QueryInterface(const Core::Guid& type, void** object) override;
        SceneModule::ISceneManager* GetSceneManager() override;
        void Run() override;

    private:
        void LoadBasicModules();
    public:
        UNIQUE_PTR(SceneModule::ISceneManager) m_scene_manager{ nullptr, Core::DestroyObject };
        System::ILogger* m_logger{ System::GetDefaultLogger() };
        Core::Pointer<LowLevelRender::IRenderModule> m_render_module{ nullptr, Core::DestroyObject };
        Core::Pointer<System::IModule> m_graphics_module{ nullptr, Core::DestroyObject };
        Core::Pointer<System::IModule> m_io_module{ nullptr, Core::DestroyObject };

        PUNK_OBJECT_DEFAULT_IMPL(Application)
    };

    Application::Application() {

        LoadBasicModules();

        m_logger->Info("Create application");
        m_scene_manager = System::CreateInstancePtr<SceneModule::ISceneManager>(SceneModule::IID_ISceneManager);

        auto loader = System::CreateInstancePtr<IoModule::IIoObserver>(IoModule::IID_IIoObserver);
        m_scene_manager->GetScene()->AddObserver(loader.get());


        auto animator_module = System::CreateInstancePtr<AnimatorModule::IAnimatorModule>(AnimatorModule::IID_IAnimatorModule);
        auto animator_observer = Core::QueryInterfacePtr<AnimatorModule::IAnimatorObserver>(animator_module.get(), AnimatorModule::IID_IAnimatorObserver);
        auto animator_processor = Core::QueryInterfacePtr<AnimatorModule::IAnimatorProcessor>(animator_module.get(), AnimatorModule::IID_IAnimatorProcessor);

        m_scene_manager->GetScene()->AddObserver(animator_observer.get());
        m_scene_manager->AddProcessor(animator_processor.get());

        m_render_module = System::CreateInstancePtr<LowLevelRender::IRenderModule>(LowLevelRender::IID_IRenderModule);

        auto render_processor = Core::QueryInterfacePtr<LowLevelRender::IRenderProcessor>(m_render_module.get(), LowLevelRender::IID_IRenderProcessor);
        auto render_observer = Core::QueryInterfacePtr<LowLevelRender::IRenderObserver>(m_render_module.get(), LowLevelRender::IID_IRenderObserver);
        m_scene_manager->GetScene()->AddObserver(render_observer.get());
        m_scene_manager->AddProcessor(render_processor.get());
    }

    Application::~Application() {
        m_scene_manager->Release();
        m_scene_manager = nullptr;
    }

    void Application::LoadBasicModules() {
        std::vector<Core::String> modules{ {L"punk_graphics", L"punk_loader", L"punk_scene", L"punk_attributes", L"punk_ai", L"punk_application", L"punk_core",
                L"punk_error", L"punk_font", L"punk_image",
                L"punk_math", L"punk_render", L"punk_string", L"punk_system",
                L"punk_animator" } };

        for (auto& module : modules) {
            try{
                System::LoadModule(module);
                m_logger->Info("Module loaded '" + module + "'");
            }
            catch (System::Error::SystemException& e) {
                m_logger->Error("Can't load " + module + ". " + e.Message() + ". " + e.GetStack());
            }
            catch (...) {
                m_logger->Error("Can't load " + module);
            }
        }
    }
    SceneModule::ISceneManager* Application::GetSceneManager() {
        return m_scene_manager.get();
    }

    void Application::Run() {
        System::ITimerPointer timer = System::CreateInstancePtr<System::ITimer>(System::IID_ITimer);
        timer->Reset();
        int frame = 0;
        float t = 0;
        while (!m_scene_manager->IsTerminated()) {
            float dt = timer->GetElapsedMiliseconds();
            timer->Reset();			
			m_scene_manager->Update(dt);				
            frame++;
            t += dt;
            if (t > 1000.0f) {
                t = 0;
                System::GetDefaultLogger()->Info(Core::String("FPS: {0}").arg(frame));
                frame = 0;
            }
        }
    }

    void Application::QueryInterface(const Core::Guid& type, void** object) {
        Core::QueryInterface(this, type, object, { IID_IApplication, Core::IID_IObject });
    }

    PUNK_REGISTER_CREATOR(IID_IApplication, (System::CreateInstance<Application, IApplication>));
}
PUNK_ENGINE_END

//{
//
//	Application::Application()
//		: m_time_scale_nominator(1)
//		, m_time_scale_denomiator(1)
//		, m_video_driver(nullptr)
//        , m_async_parser(new Utility::AsyncParser)
//	{
//		m_paint_engine = nullptr;
//        m_keymap = new System::KeyMap;
//        m_event_manager = new System::EventManager();
//	}
//
//	Application::~Application()
//	{		        
//	}
//
//	void Application::Clear()
//    {
//        safe_delete(m_async_parser);
//        OnDestroy();
//		safe_delete(m_font_builder);        
//        Virtual::StaticGeometry::Info.DestroyAllInstances();
//        Virtual::SkinGeometry::Info.DestroyAllInstances();
//        Virtual::Armature::Info.DestroyAllInstances();
//        Virtual::Material::Info.DestroyAllInstances();
//		safe_delete(m_paint_engine);
////		GUI::Manager::Destroy();
//		safe_delete(m_terrain_manager);
//		safe_delete(m_simulator);
//        Gpu::Destroy(m_video_driver);
//		safe_delete(m_window);
//		safe_delete(m_event_manager);
//        safe_delete(m_keymap);
//    }
//
//
//    void Application::Init(const Config& data)
//    {        
//        m_font_builder = System::GetService<Utility::IFontBuilder*>("font_manager", "font_builder");
//        m_window = System::GetService<System::Window*>("window", "window");
//
//        if (!data.gpu_config.disable_3d_graphics)
//        {
//            System::Mouse::Instance()->LockInWindow(true);
//            {
//                Gpu::VideoDriverDesc desc;
//                desc.config = data.gpu_config;
//                desc.event_manager = m_event_manager;
//                desc.window = m_window;
//                desc.font_builder = m_font_builder;
//                m_video_driver = Gpu::Init(desc);
//            }
//
//            //		{
//            //			GUI::ManagerDesc man_desc;
//            //			man_desc.adapter = this;
//            //			man_desc.event_manager = m_event_manager;
//            //			man_desc.window = m_window;
//            //			GUI::Manager::Create(man_desc);
//            //		}
//
//            {
//                m_simulator =  nullptr;
//                //	m_simulator = new Physics::Simulator;
//                //	m_simulator->Init();
//            }
//
//            {
//                Virtual::TerrainManagerDesc desc;
//                desc.memory_usage = 1024*1024*1024;
//                desc.threshold = 32.0f;
//                desc.view_size = 1024;
//                desc.simulator = m_simulator;
//                m_terrain_manager = new Virtual::TerrainManager(desc);
//            }
//
//            {
//                //			m_paint_engine = new Gpu::OpenGL::OpenGLPaintEngine;
//                //			m_paint_engine->SetSurfaceSize(GetWindow()->GetWidth(), GetWindow()->GetHeight());
//            }
//        }
//		OnInit(data);
//	}
//
//	void Application::WndOnIdleEvent(System::IdleEvent* event)
//	{
//        Idle(event);
//		//m_simulator->Update(float(event->elapsed_time_s));
//		m_event_manager->FixEvent(event);
//		m_event_manager->Process();
//
//        if (GetVideoDriver())
//            LowLevelRender();
//	}
//
//	void Application::WndOnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event)
//	{        
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event)
//	{
//        MouseRightButtonDown(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event)
//	{
//        MouseLeftButtonDown(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseHooverEvent(System::MouseHooverEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseMoveEvent(System::MouseMoveEvent* event)
//	{
//		MouseMove(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnMouseWheelEvent(System::MouseWheelEvent* event)
//	{
//		MouseWheel(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnCharEvent(System::KeyEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnWideCharEvent(System::KeyWCharEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnKeyDownEvent(System::KeyDownEvent* event)
//	{
//		KeyDown(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnKeyUpEvent(System::KeyUpEvent* event)
//	{
//		KeyUp(event);
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::WndOnResizeEvent(System::WindowResizeEvent* event)
//	{
//		Resize(event);
//	}
//
//	void Application::WndOnCreateEvent()
//	{
//	}
//
//	void Application::WndOnDestroyEvent()
//	{
//		Clear();
//	}
//
//	void Application::OnSetFocusedEvent(GUI::SetFocusedEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::OnSetUnFocusedEvent(GUI::SetUnFocusedEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::OnMouseEnterEvent(GUI::MouseEnterEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	void Application::OnMouseLeaveEvent(GUI::MouseLeaveEvent* event)
//	{
//		m_event_manager->FixEvent(event);
//	}
//
//	int Application::Run()
//	{
//		return m_window->Loop();
//	}
//
//    System::Window* Application::GetWindow() const
//	{
//		return m_window;
//	}
//
//	System::EventManager* Application::GetEventManager()
//	{
//		return m_event_manager;
//	}
//
//	Gpu::VideoDriver* Application::GetVideoDriver()
//	{
//		return m_video_driver;
//	}
//
//    Utility::AsyncParser* Application::GetAsyncParser()
//    {
//        return m_async_parser;
//    }
//
//	GUI::Manager* Application::GetGUIManager()
//	{
//		return GUI::Manager::Instance();
//	}
//
//	Virtual::TerrainManager* Application::GetTerrainManager()
//	{
//		return m_terrain_manager;
//	}
//
//	void Application::SetTimeScale(int64_t nominator, int64_t denominator)
//	{
//		m_time_scale_nominator = nominator;
//		m_time_scale_denomiator = denominator;
//	}
//
//	Physics::Simulator* Application::GetSimulator()
//	{
//		return m_simulator;
//	}
//
//	Gpu::PaintEngine* Application::GetPaintEngine()
//	{
//		return m_paint_engine;
//	}
//
//    void Application::OnRender(Gpu::Frame*)
//    {
//
//    }
//
//	void Application::OnInit(const Config &value)
//	{
//
//	}
//
//    void Application::LowLevelRender()
//    {
//        Gpu::VideoDriver* driver = GetVideoDriver();
//        if (!driver)
//            return;
//
//        Gpu::Frame* frame = driver->BeginFrame();
//        if (!frame)
//            return;
//
//        OnRender(frame);
//        driver->EndFrame(frame);
//    }
//
//#ifdef _WIN32
//    LRESULT Application::CustomDefWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
//    {
//        return GetWindow()->CustomDefWindowProc(wnd, msg, wParam, lParam);
//    }
//#endif
//
//	void Application::OnResize(System::WindowResizeEvent *event)
//	{}
//
//	void Application::OnKeyDown(System::KeyDownEvent *event)
//	{}
//
//	void Application::OnKeyUp(System::KeyUpEvent *event)
//	{}
//
//	void Application::OnMouseWheel(System::MouseWheelEvent *event)
//	{}
//
//	void Application::OnMouseMove(System::MouseMoveEvent *event)
//	{}
//
//    void Application::OnDestroy()
//    {}
//
//    void Application::OnIdle(System::IdleEvent *event)
//    {}
//
//    void Application::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event)
//    {}
//
//    void Application::OnMouseRightButtonDown(System::MouseRightButtonDownEvent *event)
//    {}
//
//	void Application::Resize(System::WindowResizeEvent *event)
//	{
//		m_event_manager->FixEvent(event);
//
//		auto p = GetPaintEngine();
//		if (p)
//			p->SetSurfaceSize(event->width, event->height);
//
//		auto driver = GetVideoDriver();
//		if (driver)
//		{
//			driver->SetViewport(0, 0, event->width, event->height);
//			OnResize(event);
//		}		
//	}
//
//	void Application::KeyDown(System::KeyDownEvent *event)
//	{
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_KEY_DOWN);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                int key = (*it).first;
//                if (key == event->key)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//            }
//        }
//		OnKeyDown(event);
//	}
//
//	void Application::KeyUp(System::KeyUpEvent *event)
//	{
//		OnKeyUp(event);
//	}
//
//	void Application::MouseWheel(System::MouseWheelEvent *event)
//	{
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_MOUSE_WHEEL);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                int key = (*it).first;
//                if (key == event->delta)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//            }
//        }
//
//		OnMouseWheel(event);
//	}
//
//	void Application::MouseMove(System::MouseMoveEvent *event)
//	{
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_MOUSE_MOVE);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                int key = (*it).first;
//                if (key == -1)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//                else if (key == System::Mouse::LEFT_BUTTON && event->leftButton)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//                else if (key == System::Mouse::RIGHT_BUTTON && event->rightButton)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//                else if (key == System::Mouse::MIDDLE_BUTTON && event->middleButton)
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//            }
//        }
//
//		OnMouseMove(event);
//	}
//
//    void Application::MouseLeftButtonDown(System::MouseLeftButtonDownEvent* event)
//    {
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_MOUSE_LBUTTON_DOWN);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                for (const auto& handler : (*it).second)
//                {
//                    handler(event);
//                }
//            }
//        }
//        OnMouseLeftButtonDown(event);
//    }
//
//    void Application::Idle(System::IdleEvent *event)
//    {
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_KEYBOARD_HOLD_BUTTON);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                int key = (*it).first;
//                if (System::Keyboard::Instance()->GetKeyState(key))
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//            }
//        }
//        //  process hold mouse
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_MOUSE_HOLD_BUTTON);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                int key = (*it).first;
//                if (System::Mouse::Instance()->GetButtonState((System::Mouse::MouseButtons)key))
//                {
//                    for (const auto& handler : (*it).second)
//                    {
//                        handler(event);
//                    }
//                }
//            }
//        }
//
//        OnIdle(event);
//    }
//
//    void Application::MouseRightButtonDown(System::MouseRightButtonDownEvent *event)
//    {
//        auto map = GetKeyMap();
//        //  process hold keyboard
//        {
//            const System::KeyMap::ActionsCollection& actions = map->Actions(System::EVENT_MOUSE_RBUTTON_DOWN);
//            for (System::KeyMap::ActionsCollection::const_iterator it = actions.begin(); it != actions.end(); ++it)
//            {
//                for (const auto& handler : (*it).second)
//                {
//                    handler(event);
//                }
//            }
//        }
//        OnMouseRightButtonDown(event);
//    }
//
//    System::KeyMap* Application::GetKeyMap()
//    {
//        return m_keymap;
//    }
//}
