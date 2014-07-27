///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////
using namespace Punk::Engine::Tools;

ModuleManagerDialog::ModuleManagerDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1024,768 ), wxSize( 2048,2048 ) );
	
	wxBoxSizer* m_main_sizer;
	m_main_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_info_sizer;
	m_info_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* m_list_sizer;
	m_list_sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Modules") ), wxVERTICAL );
	
	m_loaded_modules_list = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	m_loaded_modules_list->SetMinSize( wxSize( 200,100 ) );
	
	m_list_sizer->Add( m_loaded_modules_list, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* m_list_operations_sizer;
	m_list_operations_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_add = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_list_operations_sizer->Add( m_add, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	m_remove_module = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	m_list_operations_sizer->Add( m_remove_module, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	
	m_list_sizer->Add( m_list_operations_sizer, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxFIXED_MINSIZE, 5 );
	
	
	m_info_sizer->Add( m_list_sizer, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* m_module_data_sizer;
	m_module_data_sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Info") ), wxVERTICAL );
	
	wxBoxSizer* m_name_sizer;
	m_name_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_module_name = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_module_name->Wrap( -1 );
	m_name_sizer->Add( m_module_name, 0, wxALL, 5 );
	
	m_name_value = new wxStaticText( this, wxID_ANY, wxT("[Unknown]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name_value->Wrap( -1 );
	m_name_sizer->Add( m_name_value, 0, wxALL, 5 );
	
	
	m_module_data_sizer->Add( m_name_sizer, 0, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* m_path;
	m_path = new wxBoxSizer( wxHORIZONTAL );
	
	m_module_path = new wxStaticText( this, wxID_ANY, wxT("Path"), wxDefaultPosition, wxDefaultSize, 0 );
	m_module_path->Wrap( -1 );
	m_path->Add( m_module_path, 0, wxALL, 5 );
	
	m_module_path_value = new wxStaticText( this, wxID_ANY, wxT("[Unknown]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_module_path_value->Wrap( -1 );
	m_path->Add( m_module_path_value, 0, wxALL, 5 );
	
	
	m_module_data_sizer->Add( m_path, 0, wxEXPAND, 5 );
	
	
	m_info_sizer->Add( m_module_data_sizer, 2, wxALIGN_TOP|wxALL|wxEXPAND, 5 );
	
	
	m_main_sizer->Add( m_info_sizer, 1, wxEXPAND, 5 );
	
	m_ok = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	m_main_sizer->Add( m_ok, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( m_main_sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleAdd ), NULL, this );
	m_remove_module->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleRemove ), NULL, this );
	m_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnOk ), NULL, this );
}

ModuleManagerDialog::~ModuleManagerDialog()
{
	// Disconnect Events
	m_add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleAdd ), NULL, this );
	m_remove_module->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleRemove ), NULL, this );
	m_ok->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnOk ), NULL, this );
	
}

SceneGraphPanel::SceneGraphPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
}

SceneGraphPanel::~SceneGraphPanel()
{
}
