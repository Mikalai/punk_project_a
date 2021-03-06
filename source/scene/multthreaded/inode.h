#ifndef INODE_H
#define INODE_H

#include <memory>
#include <config.h>
#include <cstdint>
#include <core/iobject.h>
#include <core/action.h>
#include "attribute.h"
#include "node_state.h"

PUNK_ENGINE_BEGIN
namespace Core { class Rtti; }
namespace Scene {

    class ISceneGraph;

	DEFINE_PUNK_GUID(IID_INode, "995D98AA-3787-4115-B445-496DA2E5067B");

    class INode : public virtual Core::IObject {
    public:
        virtual void SetAttribute(IAttribute* value) = 0;
        virtual IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const = 0;
		virtual int GetAttributesCount(std::uint64_t type) const = 0;
		virtual std::vector<IAttribute*> GetAttributes(std::uint64_t type) const = 0;
        virtual void RemoveAttribute(const Core::String& name, std::uint64_t type) = 0;
        virtual NodeState GetState() const = 0;
        virtual void SetState(NodeState value) = 0;
        virtual ISceneGraph* GetSceneGraph() = 0;
		virtual void SetSceneGraph(ISceneGraph* graph) = 0;

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
		T* Get() {
			auto attribute = GetAttribute()
		}

        template<class T>
        const T* Get(const Core::String& name) const {
            auto attribute = GetAttribute(name, typeid(T).hash_code());
            return attribute ? attribute->Get<T>() : nullptr;
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
        void Set(const Core::String& name, T* value) {
            SetAttribute(new Attribute<T>(name, value, true));
        }

        template<class T>
        void Set(const Core::String &name, T value) {
            SetAttribute(new Attribute<T>(name, new T(value), true));
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

    using INodeUniquePtr = std::unique_ptr<INode, void (*)(INode*)>;
    
}
PUNK_ENGINE_END

#endif // INODE_H
