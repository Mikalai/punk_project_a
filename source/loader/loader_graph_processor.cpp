#include <core/object.h>
#include "loader_cache.h"
#include "loader_graph_processor.h"
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    LoaderGraphProcessor::LoaderGraphProcessor()
    {
    }

    unsigned void LoaderGraphProcessorThread(void* _p) {
        LoaderGraphProcessor* gp = (LoaderGraphProcessor*)_p;
        while (!gp->IsFinish()) {
            gp->WaitUpdate();
            gp->InternalUpdate();
            gp->EndUpdate();
        }
    }

    void LoaderGraphProcessor::BeginUpdate(int dt_ms) {
        m_update_mutex.Lock();
        m_last_update_step = dt_ms;
        m_graph->Lock();
        PreUpdate();
        m_graph->Unlock();
        m_update_mutex.Unlock();
    }

    void LoaderGraphProcessor::WaitUpdateFinish() {
        m_update_mutex.Lock();
    }

    void LoaderGraphProcessor::WaitUpdate() {
        m_update_mutex.Lock();
    }

    void LoaderGraphProcessor::EndUpdate() {
        m_graph->Lock();
        PostUpdate();
        m_graph->Unlock();
        m_update_mutex.Unlock();
    }

    void LoaderGraphProcessor::InternalUpdate(int dt_ms)
    {
        for (LoaderCache* cache : m_caches) {
            auto loader = cache->m_task;
            if (loader->State() == AsyncParserTask::AsyncSuccess) {
                Core::Object* object = loader->Release();
                if (object) {
                    auto node = cache->m_parent;
                    node->Set(new Scene::Attribute<Core::Object>(L"Unknown", object));
                }
                cache->m_delete = true;
            }
        }
    }

    void LoaderGraphProcessor::PreUpdate() {

    }

    void LoaderGraphProcessor::PostUpdate() {
        auto it = m_caches.begin();
        while (it != m_caches.end()) {
            LoaderCache* cache = *it;
            if (cache->m_delete) {
                auto node = cache->m_parent;
                auto del = it;
                ++it;
                m_caches.erase(del);
                node->Remove<LoaderCache>(L"LoaderCache");
            }
        }
    }

    void LoaderGraphProcessor::Destroy() {

    }

    void LoaderGraphProcessor::Initialize(Scene::ISceneGraph *graph) {
        Scene::INode* graph_node = graph->GetRoot();
        Process(graph_node);
    }

    void LoaderGraphProcessor::Process(Scene::INode *node){
        if (node->GetState() == Scene::NodeState::Inactive) {
            auto type = node->Get<Core::String>(L"Type");
            if (type && *type == L"FileProxy") {
                auto path = node->Get<Core::String>(L"Filename");
                if (path) {
                    auto cache = node->Get<LoaderCache>(L"LoaderCache");
                    if (!cache) {
                        LoaderCache* cache = new LoaderCache();
                        cache->m_task = new AsyncParserTask(*path);
                        cache->m_parent = node;
                        m_parser->Add(cache->m_task);
                        node->Set<LoaderCache>(cache);
                    }
                }
            }
        }        
        else if (node->GetState() == Scene::NodeState::PendingDelete) {

        }
    }

    void LoaderGraphProcessor::BeginUpdate(int dt_ms) {
}

PUNK_ENGINE_END
