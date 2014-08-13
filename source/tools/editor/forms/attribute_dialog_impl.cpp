#include "attribute_dialog_impl.h"
#include <system/factory/module.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	AttributeDialogImpl::AttributeDialogImpl(wxWindow* parent)
		:
		AttributeDialog(parent)
	{
		m_attributes_panel = nullptr;
		//m_attributes_panel = new AttributePanelImpl(this);
		//m_name_sizer1->Add(m_attributes_panel);
		auto manager = Common::GetAttributesManager();
		if (manager) {
			m_groups->Clear();
			for (std::uint32_t group_index = 0, max_group_index = manager->GetGroupsCount(); group_index < max_group_index; ++group_index) {
				auto name = manager->GetGroupName(group_index);
				m_groups->Append(Common::PunkStringToWxString(name), (void*)group_index);
			}
		}
	}

	void AttributeDialogImpl::SetObject(Core::Pointer<Core::IObject> value)
	{
		m_object = value;		
		UpdatePanel();
	}

	void AttributeDialogImpl::SetObjectName(const Core::String& value) {
		m_name = value;
		m_attribute_name->SetValue(Common::PunkStringToWxString(m_name));
	}

	void AttributeDialogImpl::UpdatePanel() {
		delete m_attributes_panel;
		m_attributes_panel = new AttributePanelImpl(this);
		m_parameters_sizer->Add(m_attributes_panel, 1, wxALL | wxEXPAND, 5);
		m_parameters_sizer->Layout();
		if (m_object) {
			auto editable = Core::QueryInterfacePtr<IEditableElement>(m_object, IID_IEditableElement);
			if (editable) {
				editable->AddToPanel(m_attributes_panel);
			}
		}
	}

	void AttributeDialogImpl::OnGroupSelected(wxCommandEvent& event) {
		auto manager = Common::GetAttributesManager();
		if (manager) {
			if (event.GetSelection() != wxNOT_FOUND) {
				auto group_index = (std::uint32_t)m_groups->GetClientData(event.GetSelection());
				m_attributes->Clear();
				for (std::uint32_t attribute_index = 0, max_attribute_index = manager->GetAttributesCount(group_index); attribute_index < max_attribute_index; ++attribute_index) {
					auto attribute_name = manager->GetAttributeName(group_index, attribute_index);
					m_attributes->Append(Common::PunkStringToWxString(attribute_name), (void*)attribute_index);
				}
			}
		}
	}

	Core::Pointer<Core::IObject> AttributeDialogImpl::CreateObject() {
		auto manager = Common::GetAttributesManager();
		if (manager) {
			auto group_sel = m_groups->GetSelection();
			if (group_sel != wxNOT_FOUND) {
				auto group_index = (std::uint32_t)m_groups->GetClientData(group_sel);

				auto attribute_sel = m_attributes->GetSelection();
				if (attribute_sel != wxNOT_FOUND) {
					auto attribute_index = (std::uint32_t)m_attributes->GetClientData(attribute_sel);
					auto clsid = manager->GetAttributeClsid(group_index, attribute_index);
					return System::CreateInstancePtr<Core::IObject>(clsid, Core::IID_IObject);
				}
			}
		}
	}

	void AttributeDialogImpl::OnItemChanged(wxCommandEvent& event) {		
		m_object = CreateObject();
		UpdatePanel();
	}

	void AttributeDialogImpl::OnOk(wxCommandEvent& event)
	{
		m_name = Common::WxStringToPunkString(m_attribute_name->GetValue());		
		EndModal(wxID_OK);
	}

	void AttributeDialogImpl::OnCancel(wxCommandEvent& event)
	{
		EndModal(wxID_CANCEL);
	}
}
PUNK_ENGINE_END
