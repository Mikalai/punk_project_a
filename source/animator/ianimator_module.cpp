#include <core/module.h>
#include <system/factory/module.h>
#include <attributes/module.h>
#include "ianimator_module.h"
#include "ianimator_observer.h"
#include "ianimator_processor.h"


PUNK_ENGINE_BEGIN
namespace AnimatorModule {

	class Animator : public IAnimatorModule, public IAnimatorObserver, public IAnimatorProcessor {
	public:
        Animator();
		virtual ~Animator();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAnimatorObserver
		void SetScene(SceneModule::IScene* value) override;
		void OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;
		void OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) override;
		void OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;

		//	IAnimatorProcessor
		void SetSceneManager(SceneModule::ISceneManager* manager) override;
		void Update(float dt) override;
		void Terminate() override;

	private:
		
		void Process(SceneModule::INode* node);
		void OnAnimationLoaded(Core::IObject* o) {
			LOG_FUNCTION_SCOPE;
            auto animation = Core::QueryInterfacePtr<Attributes::IAnimation>(o, Attributes::IID_IAnimation);
			if (animation.get()) {
				animation->AddRef();
				m_animations.push_back(Core::Pointer < Attributes::IAnimation > {animation.get(), Core::DestroyObject});
				m_animation_map.AddValue(animation->GetName(), animation.get());
			}
		}

	private:
		void Clear();
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<Core::Pointer<Attributes::IAnimated>> m_animated;
		std::vector<Core::Pointer<Attributes::IAnimationPlayer>> m_players;
		Core::Pointer<SceneModule::IScene> m_scene{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::ISceneManager> m_manager{ nullptr, Core::DestroyObject };
		Core::ObjectPool<Core::String, Attributes::IAnimation*> m_animation_map;
		std::vector<Core::Pointer<Attributes::IAnimation>> m_animations;
	};

    Animator::Animator()
        : m_ref_count{ 0 }
    {
		LOG_FUNCTION_SCOPE;
    }

	Animator::~Animator() {
		LOG_FUNCTION_SCOPE;
	}

	//	IObject
	void Animator::QueryInterface(const Core::Guid& type, void** object) {
		LOG_FUNCTION_SCOPE;
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (void*)(Core::IObject*)(IAnimatorModule*)this;
			AddRef();
		}
		else if (type == IID_IAnimatorModule) {
			*object = (void*)(IAnimatorModule*)this;
			AddRef();
		}
		else if (type == IID_IAnimatorObserver) {
			*object = (void*)(IAnimatorObserver*)this;
			AddRef();
		}
		else if (type == IID_IAnimatorProcessor) {
			*object = (void*)(IAnimatorProcessor*)this;
			AddRef();
		}
		else if (type == SceneModule::IID_IProcessor) {
			*object = (void*)(SceneModule::IProcessor*)this;
			AddRef();
		}
		else if (type == SceneModule::IID_IObserver) {
			*object = (void*)(SceneModule::IObserver*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	std::uint32_t Animator::AddRef() {
		LOG_FUNCTION_SCOPE;
		return m_ref_count.fetch_add(1);        
	}

	std::uint32_t Animator::Release() {
		LOG_FUNCTION_SCOPE;
        auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	void Animator::Clear() {
		LOG_FUNCTION_SCOPE;
		m_animated.clear();
		m_players.clear();
		m_animations.clear();
	}

	void Animator::Terminate() {
		LOG_FUNCTION_SCOPE;
		Clear();
	}

	//	IAnimatorObserver
	void Animator::SetScene(SceneModule::IScene* value) {
		LOG_FUNCTION_SCOPE;
		value->AddRef();
		m_scene.reset(value);
		if (m_scene.get())
			Process(m_scene->GetRoot());
	}

	void Animator::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {
		LOG_FUNCTION_SCOPE;
        Process(child);
	}

	void Animator::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {
		LOG_FUNCTION_SCOPE;
	}

	void Animator::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
		auto animation = attribute->Get<Attributes::IAnimation>();
		if (animation) {
			animation->AddRef();
			m_animations.push_back(Core::Pointer < Attributes::IAnimation > {animation, Core::DestroyObject});
			m_animation_map.AddValue(animation->GetName(), animation);
		}
	}

	void Animator::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {
		LOG_FUNCTION_SCOPE;
	}

	void Animator::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
	}

	void Animator::Process(SceneModule::INode* node) {
		LOG_FUNCTION_SCOPE;
		auto count = node->GetAttributesCount();
		for (int i = 0; i < count; ++i) {
			auto attribute = node->GetAttribute(i);
            auto animated = Core::QueryInterfacePtr<Attributes::IAnimated>(attribute->GetRawData(), Attributes::IID_IAnimated);
			if (animated.get()) {
				animated->AddRef();
				m_animated.push_back(Core::Pointer < Attributes::IAnimated > {animated.get(), Core::DestroyObject});

				//	submit all animation for loading
				for (std::uint32_t i = 0, max_i = animated->GetAnimationsCount(); i < max_i; ++i) {
					auto name = animated->GetAnimation(i);
					if (!m_animation_map.HasValue(name)) {
						auto filename = m_scene->GetSourcePath() + name + L".action";
                        Core::Pointer<Attributes::IFileStub> file_stub = System::CreateInstancePtr<Attributes::IFileStub>(Attributes::IID_IFileStub);
						file_stub->SetFilename(filename);
						file_stub->SetCallback(new Core::Action < Animator, Core::IObject* > { this, &Animator::OnAnimationLoaded });
						node->Set<Attributes::IFileStub>(name, file_stub.get());
					}
				}
			}
		}
		
		for (int i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
			Process(node->GetChild(i));
		}
	}

	//	IAnimatorProcessor
	void Animator::SetSceneManager(SceneModule::ISceneManager* manager) {
		LOG_FUNCTION_SCOPE;
		manager->AddRef();
		m_manager.reset(manager);
	}

    void Animator::Update(float dt) {
		LOG_FUNCTION_SCOPE;
		dt /= 1000.0f; 
		for (auto& player : m_players) {			
			if (player->IsPlaying()) {
				player->Seek(Attributes::AnimationSeekDirection::Current, dt);
			}
		}

		for (auto& animated : m_animated) {
			if (!animated->GetAnimationPlayer()) {
				if (animated->GetAnimationsCount() && m_animation_map.HasValue(animated->GetAnimation(0))){
					auto animation = m_animation_map.GetValue(animated->GetAnimation(0));
                    Core::Pointer<Attributes::IAnimationPlayer> player = System::CreateInstancePtr<Attributes::IAnimationPlayer>(Attributes::IID_IAnimationPlayer);
					player->SetAnimation(animation);
					animated->SetAnimationPlayer(player.get());
					player->Start();
					player->AddRef();
					m_players.push_back(Core::Pointer < Attributes::IAnimationPlayer > {player.get(), Core::DestroyObject});
				}
			}
			if (animated->GetAnimationPlayer() && animated->GetAnimationPlayer()->IsPlaying())
				animated->Update();
		}
	}


    PUNK_REGISTER_CREATOR(IID_IAnimatorModule, (System::CreateInstance < Animator, IAnimatorModule>));
}
PUNK_ENGINE_END
