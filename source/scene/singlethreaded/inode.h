#ifndef INODE_H
#define INODE_H

#include <memory>
#include <config.h>
#include <cstdint>
#include <core/weak_pointer.h>
#include <core/iobject.h>
#include <core/action.h>
#include "iattribute.h"
#include "node_state.h"

PUNK_ENGINE_BEGIN
namespace Core { class Rtti; }
namespace SceneModule {

    class IScene;

	DECLARE_PUNK_GUID(IID_INode, "995D98AA-3787-4115-B445-496DA2E5067B");
	DECLARE_PUNK_GUID(CLSID_Node, "323255CA-8AAB-4F3A-827C-AC3A440F9B32");

    class INode : public Core::IObject {
    public:
		virtual INode* GetParent() = 0;
		virtual const INode* GetParent() const = 0;
		virtual void SetParent(INode* node) = 0;
		
		virtual void AddChild(Core::Pointer<INode> node) = 0;
		virtual void RemoveChild(Core::Pointer<INode> node) = 0;
		virtual void RemoveAllChildren() = 0;
		virtual std::uint32_t GetChildrenCount() const = 0;
		virtual Core::Pointer<INode> GetChild(std::uint32_t index) = 0;     
		virtual bool HasChild(Core::Pointer<INode> node) const = 0;
		
		virtual void AddAttribute(Core::Pointer<IAttribute> value) = 0;
		virtual std::uint32_t GetAttributesCount() const = 0;
		virtual std::uint32_t GetAttributesCount(const Core::Guid& iid) const = 0;
		virtual std::uint32_t GetAttributeIndex(const Core::String& name) const = 0;
        virtual Core::Pointer<IAttribute> GetAttribute(const Core::String& name) const = 0;		
		virtual Core::Pointer<IAttribute> GetAttribute(std::uint32_t index) const = 0;
		virtual Core::Pointer<IAttribute> GetAttribute(const Core::Guid& iid, std::uint32_t index) const = 0;
		virtual std::vector<Core::Pointer<IAttribute>> GetAttributes() const = 0;
		virtual std::vector<Core::Pointer<IAttribute>> GetAttributes(Core::Guid& type) const = 0;
        virtual void RemoveAttribute(const Core::String& name) = 0;
		virtual void RemoveAttribute(std::uint32_t index) = 0;
		virtual void RemoveAttribute(const Core::Pointer<IAttribute> value) = 0;
		virtual bool HasAttribute(Core::Pointer<IAttribute> value) const = 0;
		virtual bool HasAttribute(const Core::String& name) const = 0;
		virtual void CacheAttribute(const Core::Guid& iid) = 0;
        
		virtual NodeState GetState() const = 0;
        virtual void SetState(NodeState value) = 0;
        virtual IScene* GetSceneGraph() = 0;
		virtual void SetScene(IScene* graph) = 0;

        template<class T>
        Core::Pointer<T> Get(const Core::String& name) {
            auto attribute = GetAttribute(name, typeid(T).hash_code());
			return attribute ? attribute->Get<T>() : Core::Pointer<T>{ nullptr, Core::DestroyObject };
        }

		template<class T>
		Core::Pointer<T> GetAttributeOfType(const Core::Guid& iid, std::uint32_t index) const {
			auto attribute = GetAttribute(iid, index);
			Core::Pointer<T> res{ nullptr, Core::DestroyObject };
			if (attribute)
				res = attribute->Get<T>();
			return res;
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
        void Add(const Core::String& name, Core::Pointer<T> value) {
			auto attribute = System::CreateInstancePtr<IAttribute>(CLSID_Attribute, IID_IAttribute);
			attribute->Initialize(name, value);
			AddAttribute(attribute);
        }

		template<class T>
		Core::Pointer<INode> FindChildByAttribute(const Core::String& name) {
			if (Get<T>(name) != nullptr)
				return this;
			for (int i = 0, max_i = GetChildrenCount(); i < max_i; ++i) {
				Core::Pointer<INode> result = GetChild(i)->FindChildByAttribute<T>(name);				
				if (result)
					return result;
			}
			return nullptr;
		}
    };    
}
PUNK_ENGINE_END

#endif // INODE_H
