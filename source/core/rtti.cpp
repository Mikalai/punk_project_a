#include <sstream>
#include <vector>
#include "string/module.h"
#include "object.h"
#include "rtti.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            namespace __private {
                struct RttiImpl {
                    String m_name;
                    std::vector<const Rtti*> m_parent;
                    std::vector<Object*> instances;
                    std::uint64_t m_id;

                    RttiImpl(const String &name, std::uint64_t uid, std::initializer_list<const Rtti*> parents)
                        : m_name(name)
                        , m_parent(parents.begin(), parents.end())
                        , m_id(uid) {}

                    ~RttiImpl() {
                    }
                };
            }

            Rtti::Rtti(const String &name, std::uint64_t uid, std::initializer_list<const Rtti*> parents)
                : impl(new __private::RttiImpl(name, uid, parents)) {}

            Rtti::~Rtti() {
                delete impl;
                impl = nullptr;
            }

            const String& Rtti::GetName() const {
                return impl->m_name;
            }

            unsigned Rtti::GetId() const {
                return impl->m_id;
            }

            std::size_t Rtti::GetParentsCount() const {
                return impl->m_parent.size();
            }

            const Rtti* Rtti::GetParent(std::size_t index) const {
                return impl->m_parent[index];
            }

            bool Rtti::IsEqual(const Rtti* value) const {
                return this == value;
            }

            bool CheckIsDerived(const Rtti* parent, const Rtti* value) {
                if (value == parent)
                    return true;
                for (auto i = 0u; i < parent->GetParentsCount(); ++i) {
                    if (CheckIsDerived(parent->GetParent(i), value))
                        return true;
                }
                return false;
            }

            bool Rtti::IsDerived(const Rtti* value) const {
                return CheckIsDerived(this, value);
            }

            const String Rtti::ToString() const {
                StringList stream;
                stream << L"[" << impl->m_name << L" (" << String::Convert(impl->m_id) << L")";
                if (!impl->m_parent.empty()) {
                    for (const Rtti* p : impl->m_parent) {
                        if (p)
                            stream << L" -> " << p->ToString() << L"]";
                        else
                            stream << L"]";
                    }
                }
                else {
                    stream << L"]";
                }
                return stream.ToString();
            }

            Object* Rtti::GetInstance(std::size_t index) {
                return impl->instances[index];
            }

            const Object* Rtti::GetInstance(std::size_t index) const {
                return impl->instances[index];
            }

            void Rtti::Add(Object* value) {
                value->SetLocalIndex(impl->instances.size());
                impl->instances.push_back(value);
            }

            void Rtti::Remove(Object* value) {
                Object* o = impl->instances.back();
                if (o != value)
                {
                    impl->instances[value->GetLocalIndex()] = o;
                    o->SetLocalIndex(value->GetLocalIndex());
                }
                impl->instances.pop_back();
            }

            std::size_t Rtti::GetInstanceCount() const {
                return impl->instances.size();
            }

            const Object* HasInstance(const Rtti* meta_class, const String& name)
            {
                for (auto i = 0u; i < meta_class->GetInstanceCount(); ++i)
                {
                    auto o = meta_class->GetInstance(i);
                    if (o->GetName() == name)
                        return o;
                }
                return nullptr;
            }
        }
    }
}
