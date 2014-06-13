#include <core/ifactory.h>
#include <attributes/module.h>
#include "ianimator_module.h"
#include "ianimator_observer.h"
#include "ianimator_processor.h"


PUNK_ENGINE_BEGIN
namespace AnimatorModule {

	class Animator : public IAnimatorModule, public IAnimatorObserver, public IAnimatorProcessor {
	public:

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

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};

	Animator::~Animator() {

	}

	//	IObject
	void Animator::QueryInterface(const Core::Guid& type, void** object) {
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
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Animator::Release() {
		auto v = m_ref_count.fetch_sub(1);
		if (!v)
			delete this;
		return v;
	}

	//	IAnimatorObserver
	void Animator::SetScene(SceneModule::IScene* value) {

	}

	void Animator::OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void Animator::OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) {

	}

	void Animator::OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	void Animator::OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) {

	}

	void Animator::OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) {

	}

	//	IAnimatorProcessor
	void Animator::SetSceneManager(SceneModule::ISceneManager* manager) {

	}

	void Animator::Update(float dt) {

	}


	PUNK_REGISTER_CREATOR(IID_IAnimatorModule, (Core::CreateInstance < Animator, IAnimatorModule>));
}
PUNK_ENGINE_END
