#include <sstream>
#include "rtti.h"
#include "string/module.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            Rtti::Rtti(const String &name, unsigned uid, std::initializer_list<const Rtti*> parents)
                : m_name(name)
                , m_parent(parents.begin(), parents.end())
                , m_id(uid) {}

            Rtti::~Rtti() {}

            const String& Rtti::GetName() const {
                return m_name;
            }

            unsigned Rtti::GetId() const {
                return m_id;
            }

            std::size_t Rtti::GetParentsCount() const {
                return m_parent.size();
            }

            const Rtti* Rtti::GetParent(std::size_t index) const {
                return m_parent[index];
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
                stream << L"[" << m_name << L" (" << String::Convert(m_id) << L")";
                if (!m_parent.empty()) {
                    for (const Rtti* p : m_parent) {
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
        }
    }
}
