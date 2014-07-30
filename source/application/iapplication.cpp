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

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IApplication
        Core::Pointer<SceneModule::ISceneManager> GetSceneManager() override;
        void Run() override;

    private:
        void LoadBasicModules();
    public:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
        Core::Pointer<SceneModule::ISceneManager> m_scene_manager{ nullptr, Core::DestroyObject };
        System::ILogger* m_logger{ System::GetDefaultLogger() };
        Core::Pointer<LowLevelRender::IRenderModule> m_render_module{ nullptr, Core::DestroyObject };
        Core::Pointer<System::IModule> m_graphics_module{ nullptr, Core::DestroyObject };
        Core::Pointer<System::IModule> m_io_module{ nullptr, Core::DestroyObject };
    };

    Application::Application() {

        LoadBasicModules();

        m_logger->Info("Create application");
        m_scene_manager = System::CreateInstancePtr<SceneModule::ISceneManager>(
			SceneModule::CLSID_SceneManager, SceneModule::IID_ISceneManager);

        auto loader = System::CreateInstancePtr<IoModule::IIoObserver>(
			IoModule::CLSID_IoObserver, IoModule::IID_IIoObserver);
        m_scene_manager->GetCurrentScene()->AddObserver(loader);


        auto animator_module = System::CreateInstancePtr<AnimatorModule::IAnimatorModule>(
			AnimatorModule::CLSID_AnimatorModule,
			AnimatorModule::IID_IAnimatorModule
			);

        auto animator_observer = Core::QueryInterfacePtr<AnimatorModule::IAnimatorObserver>(animator_module, AnimatorModule::IID_IAnimatorObserver);
        auto animator_processor = Core::QueryInterfacePtr<AnimatorModule::IAnimatorProcessor>(animator_module, AnimatorModule::IID_IAnimatorProcessor);

        m_scene_manager->GetCurrentScene()->AddObserver(animator_observer);
        m_scene_manager->AddProcessor(animator_processor);

		m_render_module = System::CreateInstancePtr<LowLevelRender::IRenderModule>(
			LowLevelRender::CLSID_Render, 
			LowLevelRender::IID_IRender
			);

        auto render_processor = Core::QueryInterfacePtr<LowLevelRender::IRenderProcessor>(m_render_module, LowLevelRender::IID_IRenderProcessor);
        auto render_observer = Core::QueryInterfacePtr<LowLevelRender::IRenderObserver>(m_render_module, LowLevelRender::IID_IRenderObserver);
        m_scene_manager->GetCurrentScene()->AddObserver(render_observer);
        m_scene_manager->AddProcessor(render_processor);
    }

    Application::~Application() {
    }

    void Application::LoadBasicModules() {
        std::vector<Core::String> modules{ {L"punk_graphics", L"punk_loader", L"punk_scene", L"punk_attributes", L"punk_ai", L"punk_application", L"punk_core",
                L"punk_error", L"punk_font", L"punk_image",
                L"punk_math", L"punk_render", L"punk_string", L"punk_system",
                L"punk_animator" } };

        for (auto& module : modules) {
            try{
                System::LoadPunkModule(module);
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
    
	Core::Pointer<SceneModule::ISceneManager> Application::GetSceneManager() {
        return m_scene_manager;
    }

    void Application::Run() {
        Core::Pointer<System::ITimer> timer = System::CreateInstancePtr<System::ITimer>(System::CLSID_Timer, System::IID_ITimer);
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

	std::uint32_t Application::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Application::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

    PUNK_REGISTER_CREATOR(CLSID_Application, (System::CreateInstance<Application, IApplication>));
}
PUNK_ENGINE_END
