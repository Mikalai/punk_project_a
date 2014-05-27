#include <string/module.h>
#include <algorithm>
#include "iprocessor.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	DEFINE_PUNK_GUID(IID_IProcessor, "2E907E18-8D08-401E-9C83-0710D9CA0CA4");

	/*SceneProcessor::SceneProcessor()
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

    void SceneProcessor::Update(int dt_ms) {
        Command cmd;
        cmd.code = Code::Update;
        cmd.update.m_dt = dt_ms;
        AddCommand(cmd);
    }

    void SceneProcessor::ClearScene() {
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

    void SceneProcessor::RegisterGraphProcessor(IGraphProcessor *proc) {
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
            m_scene_graph = CreateSceneFromFile(cmd.set_new_scene.datapath, cmd.set_new_scene.filename);
            std::for_each(m_proc.begin(), m_proc.end(), [&](IGraphProcessor* p) {
                p->SetGraph(m_scene_graph.get());
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

	void SceneProcessor::SetSceneFile(const Core::String& datapath, const Core::String& filename) {
		Command cmd;
		cmd.code = Code::SetNewScene;
		filename.ToWchar(cmd.set_new_scene.filename, MAX_PATH);
		datapath.ToWchar(cmd.set_new_scene.datapath, MAX_PATH);
		AddCommand(cmd);
	}

	const Core::String SceneProcessor::GetSceneFile() const {
		return m_scene_file;
	}

	const Core::String SceneProcessor::GetDataPath() const {
		return m_data_path;
	}*/
}
PUNK_ENGINE_END
