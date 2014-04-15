#include <string/module.h>
#include <algorithm>
#include "scene_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {


    SceneProcessor::SceneProcessor()
    {        
    }

    SceneProcessor::~SceneProcessor() {
        for (IGraphProcessor* p : m_proc) {
            p->StopProcessing();
        }

        while (!m_proc.empty()) {
            m_proc.back()->Destroy();
            delete m_proc.back();
            m_proc.pop_back();
        }
    }

    void SceneProcessor::Run(void *data) {
        while (true) {
            m_lock.Lock();
            while (m_commands.empty())
                m_lock.Wait();
            Command cmd = m_commands.front();
            m_commands.pop_front();
            m_lock.Unlock();
            if (ProcessRequest(cmd))
                return;
        }
    }

    void SceneProcessor::SetSceneFile(const Core::String& filename) {
        Command cmd;
        cmd.code = Code::SetNewScene;
        filename.ToWchar(cmd.set_new_scene.filename, MAX_PATH);
        AddCommand(cmd);
    }

    void SceneProcessor::Update(int dt_ms) {
        Command cmd;
        cmd.code = Code::Update;
        cmd.update.m_dt = dt_ms;
        AddCommand(cmd);
    }

    void SceneProcessor::DestroyScene() {
        Command cmd;
        cmd.code = Code::DestroyScene;
        AddCommand(cmd);
    }

    void SceneProcessor::Terminate() {
        Command cmd;
        cmd.code = Code::Terminate;
        AddCommand(cmd);
    }

    void SceneProcessor::AddCommand(const Command &cmd) {
        m_lock.Lock();
        m_commands.push_back(cmd);
        m_lock.PulseAll();
        m_lock.Unlock();
    }

    SceneProcessor::RegisterGraphProcessor(IGraphProcessor *proc) {
        m_proc.push_back(proc);
    }

    bool SceneProcessor::ProcessRequest(const Command& cmd) {
        if (cmd.code == Code::Update) {
            for (IGraphProcessor* proc : m_proc) {
                proc->WaitUpdateFinish();
            }

            for (IGraphProcessor* proc : m_proc) {
                proc->BeginUpdate(cmd.update.m_dt);
            }
            return false;
        }
        else if (cmd.code == Code::SetNewScene) {
            Command clear;
            clear.code = Code::DestroyScene;
            ProcessRequest(clear);
            m_scene_graph = CreateSceneFromFile(cmd.set_new_scene.m_filepath);
            std::for_each(m_proc.begin(), m_proc.end(), [](IGraphProcessor* p) {
                p->Initialize(m_scene_graph.get());
            });
            return false;
        }
        else if (cmd.code == Code::DestroyScene) {
            for (IGraphProcessor* p : m_proc) {
                p->StopProcessing();
            }
            for (IGraphProcessor* p : m_proc) {
                p->WaitProcessingComplete();
            }
            return false;
        }
        else if (cmd.code == Code::Terminate) {
            for (IGraphProcessor* p : m_proc) {
                p->StopProcessing();
            }
            for (IGraphProcessor* p : m_proc) {
                p->WaitProcessingComplete();
            }
            return true;
        }
    }

    void SceneProcessor::Update(int dt_ms) {
        ProcessRequest(m_current_request.top(), dt_ms);
    }
}
PUNK_ENGINE_END
