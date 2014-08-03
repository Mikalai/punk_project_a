///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "forms.h"

#include "new_node.png.h"
#include "new_scene.png.h"
#include "opened_folder.png.h"
#include "save.png.h"
#include "show_detailed_graph.png.h"
#include "show_objects_graph.png.h"

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

EditorMainWindowBase::EditorMainWindowBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1024,768 ), wxDefaultSize );
	
	wxBoxSizer* m_global_sizer;
	m_global_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_menu_sizer;
	m_menu_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* m_scene_ribbon_sizer;
	m_scene_ribbon_sizer = new wxBoxSizer( wxVERTICAL );
	
	m_scene_ribbon_bar = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE );
	m_scene_ribbon_bar->SetArtProvider(new wxRibbonDefaultArtProvider); 
	m_editor_page = new wxRibbonPage( m_scene_ribbon_bar, wxID_ANY, wxT("Editor") , wxNullBitmap , 0 );
	m_file_ribbon_panel = new wxRibbonPanel( m_editor_page, wxID_ANY, wxT("File") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_file_toolbar = new wxRibbonToolBar( m_file_ribbon_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_file_toolbar->AddTool( wxID_ANY, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxEmptyString);
	m_tools_manager = new wxRibbonPanel( m_editor_page, wxID_ANY, wxT("Panel manager") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_panel_manager_toolbar = new wxRibbonToolBar( m_tools_manager, ID_EDITOR_PANEL_MANAGER_TOGGLE_BOTTOM_PANEL, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel_manager_toolbar->AddToggleTool( ID_EDITOR_TOGGLE_BOTTOM_PANEL, wxArtProvider::GetBitmap( wxART_TICK_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_panel_manager_toolbar->AddToggleTool( ID_EDITOR_TOGGLE_LOG, wxArtProvider::GetBitmap( wxART_TICK_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_panel_manager_toolbar->AddToggleTool( ID_EDITOR_TOGGLE_FULLSCREEN, wxArtProvider::GetBitmap( wxART_TICK_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_do_undo_panel = new wxRibbonPanel( m_editor_page, wxID_ANY, wxT("Edit") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_do_undo_tool_bar = new wxRibbonToolBar( m_do_undo_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_do_undo_tool_bar->AddTool( ID_EDITOR_UNDO, wxArtProvider::GetBitmap( wxART_UNDO, wxART_TOOLBAR ), wxEmptyString);
	m_do_undo_tool_bar->AddTool( ID_EDITOR_REDO, wxArtProvider::GetBitmap( wxART_REDO, wxART_TOOLBAR ), wxEmptyString);
	m_engine_page = new wxRibbonPage( m_scene_ribbon_bar, wxID_ANY, wxT("Engine") , wxNullBitmap , 0 );
	m_modules_panel = new wxRibbonPanel( m_engine_page, wxID_ANY, wxT("Modules") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_module_toolbar = new wxRibbonToolBar( m_modules_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_VIEW, wxArtProvider::GetBitmap( wxART_LIST_VIEW, wxART_TOOLBAR ), wxEmptyString);
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_LOAD, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxEmptyString);
	m_module_toolbar->AddTool( ID_ENGINE_MODULES_UNLOAD, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_scene_assets_page = new wxRibbonPage( m_scene_ribbon_bar, wxID_ANY, wxT("Scene") , wxNullBitmap , 0 );
	m_scene_ribbon_bar->SetActivePage( m_scene_assets_page ); 
	m_scene_file_operations = new wxRibbonPanel( m_scene_assets_page, wxID_ANY, wxT("Scene") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_scene_file_operation_bar = new wxRibbonToolBar( m_scene_file_operations, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_scene_file_operation_bar->AddTool( ID_SCENE_LOAD, opened_folder_png_to_wx_bitmap(), wxEmptyString);
	m_scene_file_operation_bar->AddTool( ID_SCENE_SAVE, save_png_to_wx_bitmap(), wxEmptyString);
	m_assets_manager_panel = new wxRibbonPanel( m_scene_assets_page, wxID_ANY, wxT("Assets") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_assets_manager_toolbar = new wxRibbonToolBar( m_assets_manager_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_assets_manager_toolbar->AddTool( ID_SCENE_ASSETS_LOAD, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxEmptyString);
	m_assets_manager_toolbar->AddTool( ID_SCENE_ASSETS_REMOVE, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_assets_manager_toolbar->AddTool( ID_SCENE_ASSETS_PROPERTY, wxArtProvider::GetBitmap( wxART_TIP, wxART_TOOLBAR ), wxEmptyString);
	m_node_panel = new wxRibbonPanel( m_scene_assets_page, wxID_ANY, wxT("Nodes manager") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_node_panel_bar = new wxRibbonToolBar( m_node_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_node_panel_bar->AddTool( ID_SCENE_NEW_SCENE, new_scene_png_to_wx_bitmap(), wxEmptyString);
	m_node_panel_bar->AddTool( ID_SCENE_DELETE_SCENE, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_node_panel_bar->AddTool( ID_SCENE_NEW_NODE, new_node_png_to_wx_bitmap(), wxEmptyString);
	m_node_panel_bar->AddTool( ID_SCENE_NODE_DELETE, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_TOOLBAR ), wxEmptyString);
	m_scene_ribbon_bar->Realize();
	
	m_scene_ribbon_sizer->Add( m_scene_ribbon_bar, 1, wxALL|wxEXPAND, 0 );
	
	
	m_menu_sizer->Add( m_scene_ribbon_sizer, 1, wxEXPAND, 5 );
	
	
	m_global_sizer->Add( m_menu_sizer, 0, wxEXPAND, 0 );
	
	wxBoxSizer* m_central_hor_layout;
	m_central_hor_layout = new wxBoxSizer( wxHORIZONTAL );
	
	m_left_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_left_notebook = new wxNotebook( m_left_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT );
	m_scene_panel = new wxPanel( m_left_notebook, ID_SCENE_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_scene_panel_sizer;
	m_scene_panel_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* m_scene_sizer;
	m_scene_sizer = new wxStaticBoxSizer( new wxStaticBox( m_scene_panel, wxID_ANY, wxT("Scene") ), wxVERTICAL );
	
	m_scenes_combobox = new wxComboBox( m_scene_panel, ID_SCENE_CURRENT_SCENE_CHANGED, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT ); 
	m_scenes_combobox->Enable( false );
	
	m_scene_sizer->Add( m_scenes_combobox, 0, wxALL|wxEXPAND, 0 );
	
	
	m_scene_panel_sizer->Add( m_scene_sizer, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* m_scene_graph;
	m_scene_graph = new wxStaticBoxSizer( new wxStaticBox( m_scene_panel, wxID_ANY, wxT("Graph") ), wxVERTICAL );
	
	m_toolBar1 = new wxToolBar( m_scene_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_detailed_graph = m_toolBar1->AddTool( ID_SCENE_SHOW_DETAILED_GRAPH, wxT("tool"), show_detailed_graph_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Show detailed scene graph"), wxEmptyString, NULL ); 
	
	m_objects_graph = m_toolBar1->AddTool( ID_SCENE_SHOW_OBJECTS_GRAPH, wxT("tool"), show_objects_graph_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Show objects level graph"), wxEmptyString, NULL ); 
	
	m_toolBar1->Realize(); 
	
	m_scene_graph->Add( m_toolBar1, 0, wxEXPAND, 5 );
	
	m_scene_tree_graph = new wxDataViewCtrl( m_scene_panel, ID_SCENE_TREE_GRAPH, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES|wxDV_SINGLE|wxDV_VERT_RULES );
	m_scene_graph->Add( m_scene_tree_graph, 1, wxALL|wxEXPAND, 5 );
	
	
	m_scene_panel_sizer->Add( m_scene_graph, 1, wxEXPAND, 5 );
	
	
	m_scene_panel->SetSizer( m_scene_panel_sizer );
	m_scene_panel->Layout();
	m_scene_panel_sizer->Fit( m_scene_panel );
	m_left_notebook->AddPage( m_scene_panel, wxT("Scene"), false );
	
	bSizer14->Add( m_left_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	m_left_panel->SetSizer( bSizer14 );
	m_left_panel->Layout();
	bSizer14->Fit( m_left_panel );
	m_central_hor_layout->Add( m_left_panel, 1, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* m_central_layout;
	m_central_layout = new wxBoxSizer( wxVERTICAL );
	
	m_mid_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mid_panel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_mid_panel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	m_central_layout->Add( m_mid_panel, 3, wxEXPAND | wxALL, 0 );
	
	m_bottom_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_bottom_panel_layout;
	m_bottom_panel_layout = new wxBoxSizer( wxVERTICAL );
	
	m_bottom_panel_stuff = new wxNotebook( m_bottom_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM );
	m_log_panel = new wxPanel( m_bottom_panel_stuff, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_log_layout;
	m_log_layout = new wxBoxSizer( wxVERTICAL );
	
	m_log = new wxDataViewListCtrl( m_log_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES|wxDV_ROW_LINES|wxDV_VERT_RULES );
	m_log_layout->Add( m_log, 1, wxALL|wxEXPAND, 5 );
	
	
	m_log_panel->SetSizer( m_log_layout );
	m_log_panel->Layout();
	m_log_layout->Fit( m_log_panel );
	m_bottom_panel_stuff->AddPage( m_log_panel, wxT("Log"), false );
	
	m_bottom_panel_layout->Add( m_bottom_panel_stuff, 1, wxEXPAND | wxALL, 0 );
	
	
	m_bottom_panel->SetSizer( m_bottom_panel_layout );
	m_bottom_panel->Layout();
	m_bottom_panel_layout->Fit( m_bottom_panel );
	m_central_layout->Add( m_bottom_panel, 1, wxEXPAND | wxALL, 0 );
	
	
	m_central_hor_layout->Add( m_central_layout, 3, wxEXPAND, 5 );
	
	
	m_global_sizer->Add( m_central_hor_layout, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( m_global_sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( EditorMainWindowBase::OnActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorMainWindowBase::OnClose ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::OnIdle ) );
	this->Connect( ID_EDITOR_TOGGLE_BOTTOM_PANEL, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleBottomPanel ) );
	this->Connect( ID_EDITOR_TOGGLE_LOG, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleLog ) );
	this->Connect( ID_EDITOR_TOGGLE_FULLSCREEN, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleFullscreen ) );
	this->Connect( ID_EDITOR_UNDO, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnUndo ) );
	this->Connect( ID_EDITOR_REDO, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnRedo ) );
	this->Connect( ID_ENGINE_MODULES_VIEW, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnViewModules ) );
	this->Connect( ID_ENGINE_MODULES_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnLoadModule ) );
	this->Connect( ID_ENGINE_MODULES_UNLOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnUnloadModule ) );
	this->Connect( ID_SCENE_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneLoad ) );
	this->Connect( ID_SCENE_SAVE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneSave ) );
	this->Connect( ID_SCENE_NEW_SCENE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneCreate ) );
	this->Connect( ID_SCENE_DELETE_SCENE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneDelete ) );
	this->Connect( ID_SCENE_NEW_NODE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnNodeCreate ) );
	this->Connect( ID_SCENE_NODE_DELETE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnNodeDelete ) );
	m_scenes_combobox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::OnSceneChanged ), NULL, this );
	this->Connect( m_detailed_graph->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::OnSwitchDetailedGraph ) );
	this->Connect( m_objects_graph->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::OnSwitchObjectsGraph ) );
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( EditorMainWindowBase::OnSceneGraphItemActivated ) );
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( EditorMainWindowBase::OnSceneGraphItemChanged ) );
	m_mid_panel->Connect( wxEVT_SIZE, wxSizeEventHandler( EditorMainWindowBase::OnSize ), NULL, this );
}

EditorMainWindowBase::~EditorMainWindowBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( EditorMainWindowBase::OnActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorMainWindowBase::OnClose ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorMainWindowBase::OnIdle ) );
	this->Disconnect( ID_EDITOR_TOGGLE_BOTTOM_PANEL, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleBottomPanel ) );
	this->Disconnect( ID_EDITOR_TOGGLE_LOG, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleLog ) );
	this->Disconnect( ID_EDITOR_TOGGLE_FULLSCREEN, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnToggleFullscreen ) );
	this->Disconnect( ID_EDITOR_UNDO, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnUndo ) );
	this->Disconnect( ID_EDITOR_REDO, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnRedo ) );
	this->Disconnect( ID_ENGINE_MODULES_VIEW, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnViewModules ) );
	this->Disconnect( ID_ENGINE_MODULES_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnLoadModule ) );
	this->Disconnect( ID_ENGINE_MODULES_UNLOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnUnloadModule ) );
	this->Disconnect( ID_SCENE_LOAD, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneLoad ) );
	this->Disconnect( ID_SCENE_SAVE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneSave ) );
	this->Disconnect( ID_SCENE_NEW_SCENE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneCreate ) );
	this->Disconnect( ID_SCENE_DELETE_SCENE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnSceneDelete ) );
	this->Disconnect( ID_SCENE_NEW_NODE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnNodeCreate ) );
	this->Disconnect( ID_SCENE_NODE_DELETE, wxEVT_COMMAND_RIBBONTOOL_CLICKED, wxRibbonToolBarEventHandler( EditorMainWindowBase::OnNodeDelete ) );
	m_scenes_combobox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( EditorMainWindowBase::OnSceneChanged ), NULL, this );
	this->Disconnect( m_detailed_graph->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::OnSwitchDetailedGraph ) );
	this->Disconnect( m_objects_graph->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorMainWindowBase::OnSwitchObjectsGraph ) );
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( EditorMainWindowBase::OnSceneGraphItemActivated ) );
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( EditorMainWindowBase::OnSceneGraphItemChanged ) );
	m_mid_panel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( EditorMainWindowBase::OnSize ), NULL, this );
	
}

CreateSceneDialog::CreateSceneDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* m_global_sizer;
	m_global_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* m_scene_sizer;
	m_scene_sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Name") ), wxVERTICAL );
	
	m_scene_name = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_scene_sizer->Add( m_scene_name, 0, wxALL|wxEXPAND, 5 );
	
	
	m_global_sizer->Add( m_scene_sizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_ok_cancel_sizer;
	m_ok_cancel_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_ok = new wxButton( this, ID_CREATE_SCENE_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ok_cancel_sizer->Add( m_ok, 0, wxALL, 5 );
	
	m_cancel = new wxButton( this, wxID_OK, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ok_cancel_sizer->Add( m_cancel, 0, wxALL, 5 );
	
	
	m_global_sizer->Add( m_ok_cancel_sizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( m_global_sizer );
	this->Layout();
	m_global_sizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateSceneDialog::OnOk ), NULL, this );
	m_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateSceneDialog::OnCancel ), NULL, this );
}

CreateSceneDialog::~CreateSceneDialog()
{
	// Disconnect Events
	m_ok->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateSceneDialog::OnOk ), NULL, this );
	m_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateSceneDialog::OnCancel ), NULL, this );
	
}
