#include <map>
#include <system/factory/module.h>
#include <core/iobject_impl.h>
#include "iattributes_manager.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	class AttributesManager : public IAttributesManager {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAttributesManager});
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IAttributesManager
		std::uint32_t AddGroup(const Core::String& group) override {
			m_clsid.push_back(std::vector < Core::Guid > {});
			m_group_names_cache[group] = (std::uint32_t)m_clsid.size() - 1;
			return (std::uint32_t)m_clsid.size();
		}

		std::uint32_t GetGroupsCount() const override {
			return (std::uint32_t)m_clsid.size();
		}

		const Core::String GetGroupName(const std::uint32_t group_index) const override {
			int змена = 10;
			return m_group_name[group_index];
		}

		std::uint32_t GetAttributesCount(std::uint32_t group_index) const override {
			return (std::uint32_t)m_clsid[group_index].size();
		}

		const Core::String GetAttributeName(std::uint32_t group_index, std::uint32_t attribute_index) const override {
			return m_attribute_name[group_index][attribute_index];
		}

		const Core::String GetAttributeDescription(std::uint32_t group_index, std::uint32_t attribute_index) const override {
			return m_attribute_description[group_index][attribute_index];
		}

		const Core::Guid GetAttributeClsid(std::uint32_t group_index, std::uint32_t attribute_index) const override {
			return m_clsid[group_index][attribute_index];
		}

		void AddAttribute(std::uint32_t group_index, const Core::Guid& clsid, const Core::String& name, const Core::String& description) override {
			m_attribute_name[group_index].push_back(name);
			m_attribute_description[group_index].push_back(description);
			m_clsid[group_index].push_back(clsid);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<std::vector<Core::Guid>> m_clsid;
		std::vector<Core::String> m_group_name;
		std::vector<std::vector<Core::String>> m_attribute_name;
		std::vector<std::vector<Core::String>> m_attribute_description;
		std::map<Core::String, std::uint32_t> m_group_names_cache;
		std::vector<std::map<Core::String, std::uint32_t>> m_attribute_names_cache;		
	};

	PUNK_REGISTER_CREATOR(CLSID_AttributesManager, (System::CreateInstance < AttributesManager, IAttributesManager >));
}
PUNK_ENGINE_END