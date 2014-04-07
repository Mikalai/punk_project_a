#ifndef INODE_H
#define INODE_H

#include <memory>
#include <config.h>
#include <cstdint>
#include "attribute.h"
#include "node_state.h"

PUNK_ENGINE_BEGIN
namespace Scene {

    class INode {
    public:
        virtual ~INode() = 0;
        virtual void SetAttribute(IAttribute* value) = 0;
        virtual IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const = 0;
        virtual void RemoveAttribute(const Core::String& name, std::uint64_t type) = 0;
        virtual INode* GetParent() = 0;
        virtual const INode* GetParent() const = 0;
        virtual std::uint64_t GetChildrenCount() const = 0;
        virtual INode* GetChild(std::uint64_t index) = 0;
        virtual const INode* GetChild(std::uint64_t index) const = 0;
        virtual void AddChild(INode* child) = 0;
        virtual NodeState GetState() const = 0;
        virtual void SetState(NodeState value) = 0;
        virtual void RemoveChild(INode* child, bool depth) = 0;
        virtual INode* FindChild(IAttribute* attribute, bool depth) = 0;
        virtual void AddRef() = 0;
        virtual void Release() = 0;

        template<class T>
        T* Get(const Core::String& name) {
            return GetAttribute(name, typeid(T).hash_code())->Get<T>();
        }

        template<class T>
        const T* Get(const Core::String& name) const {
            return GetAttribute(name, typeid(T).hash_code())->Get<T>();
        }

        template<class T>
        void Remove(const Core::String& name) {
            RemoveAttribute(name, typeid(T).hash_code());
        }

        template<class T>
        void Set(Attribute<T> *value) {
            SetAttribute(value);
        }
    };

    inline INode::~INode() {}

    using INodeUniquePtr = std::unique_ptr<INode, void (*)(INode*)>;

    extern "C" PUNK_ENGINE_API INodeUniquePtr CreateNode(INode* parent);
    extern "C" PUNK_ENGINE_API void DestroyNode(INode* node);
}
PUNK_ENGINE_END

#endif // INODE_H
