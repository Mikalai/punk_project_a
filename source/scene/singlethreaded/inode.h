#ifndef INODE_H
#define INODE_H

#include <memory>
#include <config.h>
#include <cstdint>
#include <core/icompound_object.h>
#include <core/action.h>
#include "attribute.h"
#include "node_state.h"

PUNK_ENGINE_BEGIN
namespace Core { class Rtti; }
namespace SceneModule {

    class IScene;

	DECLARE_PUNK_GUID(IID_INode, "995D98AA-3787-4115-B445-496DA2E5067B");

    class INode : public Core::IObject {
    public:
		virtual int GetAttributesCount() const = 0;
		virtual IAttribute* GetAttribute(int index) = 0;
		virtual void AddChild(INode* node) = 0;
		virtual std::uint32_t GetChildrenCount() const = 0;
		virtual INode* GetChild(std::uint32_t index) = 0;
        virtual void SetAttribute(IAttribute* value) = 0;
        virtual IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const = 0;
		virtual IAttribute* GetAttribute(std::uint64_t type, std::uint32_t index) const = 0;
		virtual int GetAttributesCount(std::uint64_t type) const = 0;
		virtual std::vector<IAttribute*> GetAttributes(std::uint64_t type) const = 0;
        virtual void RemoveAttribute(const Core::String& name, std::uint64_t type) = 0;
        virtual NodeState GetState() const = 0;
        virtual void SetState(NodeState value) = 0;
        virtual IScene* GetSceneGraph() = 0;
		virtual void SetScene(IScene* graph) = 0;

        ///
        /// \brief MarkToDelete
        /// Decrease internal counter
        ///
        virtual void MarkToDelete() = 0;

        ///
        /// \brief AskToDelete
        /// Increase internal counter
        ///
        virtual void AskToDelete() = 0;

        ///
        /// \brief CanDelete
        /// \return true when internal counter is zero
        ///
        virtual bool CanDelete() = 0;

        template<class T>
        T* Get(const Core::String& name) {
            auto attribute = GetAttribute(name, typeid(T).hash_code());
            return attribute ? attribute->Get<T>() : nullptr;
        }

		template<class T>
		std::uint32_t GetAttributesCountOfType() const {
			return GetAttributesCount(typeid(T).hash_code());
		}

		template<class T>
		Core::Pointer<T> GetAttributeOfType(std::uint32_t index) const {
			auto attribute = GetAttribute(typeid(T).hash_code(), index);
			return attribute ? attribute->Get<T>() : Core::Pointer < T > { nullptr, Core::DestroyObject };		
		}

        template<class T>
        const Core::Pointer<T> Get(const Core::String& name) const {
            auto attribute = GetAttribute(name, typeid(T).hash_code());
			return attribute ? attribute->Get<T>() : Core::Pointer < T > { nullptr, Core::DestroyObject };
        }

        template<class T>
        void Remove(const Core::String& name) {
            RemoveAttribute(name, typeid(T).hash_code());
        }

        template<class T>
        void Set(Attribute<T> *value) {
            SetAttribute(value);
        }

        template<class T>
        void Set(const Core::String& name, Core::Pointer<T> value) {
            SetAttribute(new Attribute<T>(name, value));
        }

		template<class T>
		INode* FindChildByAttribute(const Core::String& name) {
			if (Get<T>(name) != nullptr)
				return this;
			for (int i = 0, max_i = GetChildrenCount(); i < max_i; ++i) {
				INode* result = GetChild(i)->FindChildByAttribute<T>(name);				
				if (result)
					return result;
			}
			return nullptr;
		}
    };    
}
PUNK_ENGINE_END

#endif // INODE_H
