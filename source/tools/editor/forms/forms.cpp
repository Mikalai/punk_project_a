///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "forms.h"

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
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ModuleManagerDialog::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ModuleManagerDialog::OnInit ) );
	m_loaded_modules_list->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleManagerDialog::OnItemSelected ), NULL, this );
	m_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleAdd ), NULL, this );
	m_remove_module->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnModuleRemove ), NULL, this );
	m_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleManagerDialog::OnOk ), NULL, this );
}

ModuleManagerDialog::~ModuleManagerDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ModuleManagerDialog::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ModuleManagerDialog::OnInit ) );
	m_loaded_modules_list->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleManagerDialog::OnItemSelected ), NULL, this );
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

EditorMainWindow::EditorMainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1024,768 ), wxDefaultSize );
	
	wxBoxSizer* m_global_sizer;
	m_global_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_menu_sizer;
	m_menu_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_menu = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_file_panel = new wxPanel( m_menu, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_file_bar_sizer;
	m_file_bar_sizer = new wxBoxSizer( wxVERTICAL );
	
	m_file_ribbon_bar = new wxRibbonBar( m_file_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_file_ribbon_bar->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_file_page = new wxRibbonPage( m_file_ribbon_bar, wxID_ANY, wxT("FilePage") , wxNullBitmap , 0 );
	m_file_ribbon_panel = new wxRibbonPanel( m_file_page, wxID_ANY, wxT("File") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_file_toolbar = new wxRibbonToolBar( m_file_ribbon_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_file_toolbar->AddTool( wxID_ANY, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_BUTTON ), wxEmptyString);
	m_file_ribbon_bar->Realize();
	
	m_file_bar_sizer->Add( m_file_ribbon_bar, 1, wxALL|wxEXPAND, 0 );
	
	
	m_file_panel->SetSizer( m_file_bar_sizer );
	m_file_panel->Layout();
	m_file_bar_sizer->Fit( m_file_panel );
	m_menu->AddPage( m_file_panel, wxT("File"), true );
	m_engine_panel = new wxPanel( m_menu, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_engine_panel_sizer;
	m_engine_panel_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_modules_bar = new wxRibbonBar( m_engine_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_modules_bar->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_modules_page = new wxRibbonPage( m_modules_bar, wxID_ANY, wxT("ModulesPage") , wxNullBitmap , 0 );
	m_modules_panel = new wxRibbonPanel( m_modules_page, wxID_ANY, wxT("Modules") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_module_toolbar = new wxRibbonToolBar( m_modules_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_VIEW, wxArtProvider::GetBitmap( wxART_LIST_VIEW, wxART_BUTTON ), wxEmptyString);
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_LOAD, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_BUTTON ), wxEmptyString);
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_UNLOAD, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_BUTTON ), wxEmptyString);
	m_modules_bar->Realize();
	
	m_engine_panel_sizer->Add( m_modules_bar, 1, wxALL, 0 );
	
	
	m_engine_panel->SetSizer( m_engine_panel_sizer );
	m_engine_panel->Layout();
	m_engine_panel_sizer->Fit( m_engine_panel );
	m_menu->AddPage( m_engine_panel, wxT("Engine"), false );
	
	m_menu_sizer->Add( m_menu, 1, wxALL, 0 );
	
	
	m_global_sizer->Add( m_menu_sizer, 0, wxEXPAND, 0 );
	
	
	this->SetSizer( m_global_sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( ID_ENGINE_MODULES_VIEW, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnViewModules ) );
	this->Connect( ID_ENGINE_MODULES_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnLoadModule ) );
	this->Connect( ID_ENGINE_MODULES_UNLOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnUnloadModule ) );
}

EditorMainWindow::~EditorMainWindow()
{
	// Disconnect Events
	this->Disconnect( ID_ENGINE_MODULES_VIEW, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnViewModules ) );
	this->Disconnect( ID_ENGINE_MODULES_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnLoadModule ) );
	this->Disconnect( ID_ENGINE_MODULES_UNLOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindow::OnUnloadModule ) );
	
}
