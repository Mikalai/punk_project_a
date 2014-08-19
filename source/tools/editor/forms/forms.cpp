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
	
	m_scene_tree_graph = new wxDataViewTreeCtrl( m_scene_panel, ID_SCENE_TREE_GRAPH, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES|wxDV_SINGLE|wxDV_VERT_RULES|wxSUNKEN_BORDER );
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
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( EditorMainWindowBase::OnSceneDragBegin ) );
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler( EditorMainWindowBase::OnSceneContextMenu ) );
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( EditorMainWindowBase::OnSceneDragDrop ) );
	this->Connect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE, wxDataViewEventHandler( EditorMainWindowBase::OnSceneCheckDrop ) );
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
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( EditorMainWindowBase::OnSceneDragBegin ) );
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler( EditorMainWindowBase::OnSceneContextMenu ) );
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( EditorMainWindowBase::OnSceneDragDrop ) );
	this->Disconnect( ID_SCENE_TREE_GRAPH, wxEVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE, wxDataViewEventHandler( EditorMainWindowBase::OnSceneCheckDrop ) );
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

AttributePanel::AttributePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	m_layout = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( m_layout );
	this->Layout();
}

AttributePanel::~AttributePanel()
{
}

AttributeDialog::AttributeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* m_global_sizer;
	m_global_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_inner_sizer;
	m_inner_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* m_attributes_sizer;
	m_attributes_sizer = new wxBoxSizer( wxVERTICAL );
	
	m_groups = new wxComboBox( this, ID_ATTRIBUTE_CREATE_GROUP_CHANGED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	m_attributes_sizer->Add( m_groups, 0, wxALL|wxEXPAND, 0 );
	
	m_attributes = new wxListBox( this, ID_ATTRIBUTE_CREATE_LIST_CHANGED, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	m_attributes_sizer->Add( m_attributes, 1, wxALL|wxEXPAND, 0 );
	
	
	m_inner_sizer->Add( m_attributes_sizer, 0, wxEXPAND, 0 );
	
	wxBoxSizer* m_sizer;
	m_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_name_sizer;
	m_name_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_label_name = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_label_name->Wrap( -1 );
	m_name_sizer->Add( m_label_name, 0, wxALL, 5 );
	
	m_attribute_name = new wxTextCtrl( this, wxID_ANY, wxT("Attribute"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name_sizer->Add( m_attribute_name, 1, wxALL|wxEXPAND, 5 );
	
	
	m_sizer->Add( m_name_sizer, 0, wxEXPAND, 5 );
	
	m_parameters_sizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Parameters:") ), wxVERTICAL );
	
	
	m_sizer->Add( m_parameters_sizer, 1, wxEXPAND, 5 );
	
	
	m_inner_sizer->Add( m_sizer, 1, wxEXPAND, 5 );
	
	
	m_global_sizer->Add( m_inner_sizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_btn_sizer;
	m_btn_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_ok = new wxButton( this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btn_sizer->Add( m_ok, 0, wxALIGN_RIGHT|wxALL|wxRIGHT, 5 );
	
	m_button6 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btn_sizer->Add( m_button6, 0, wxALIGN_RIGHT|wxALL|wxRIGHT, 5 );
	
	
	m_global_sizer->Add( m_btn_sizer, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( m_global_sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_groups->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AttributeDialog::OnGroupSelected ), NULL, this );
	m_attributes->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AttributeDialog::OnItemChanged ), NULL, this );
	m_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AttributeDialog::OnOk ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AttributeDialog::OnCancel ), NULL, this );
}

AttributeDialog::~AttributeDialog()
{
	// Disconnect Events
	m_groups->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AttributeDialog::OnGroupSelected ), NULL, this );
	m_attributes->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AttributeDialog::OnItemChanged ), NULL, this );
	m_ok->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AttributeDialog::OnOk ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AttributeDialog::OnCancel ), NULL, this );
	
}

BooleanEditor::BooleanEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer24->Add( m_name, 0, wxALL|wxEXPAND, 0 );
	
	m_check_box = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_check_box, 0, wxALIGN_LEFT|wxALL|wxEXPAND, 0 );
	
	
	this->SetSizer( bSizer24 );
	this->Layout();
}

BooleanEditor::~BooleanEditor()
{
}

Vec3FloatEditor::Vec3FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer25->Add( m_name, 0, wxALL, 5 );
	
	m_x = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_x, 1, wxALL, 5 );
	
	m_y = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_y, 1, wxALL, 5 );
	
	m_z = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_z, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer25 );
	this->Layout();
	
	// Connect Events
	m_x->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnXChanged ), NULL, this );
	m_y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnYChanged ), NULL, this );
	m_z->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnZChanged ), NULL, this );
}

Vec3FloatEditor::~Vec3FloatEditor()
{
	// Disconnect Events
	m_x->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnXChanged ), NULL, this );
	m_y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnYChanged ), NULL, this );
	m_z->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec3FloatEditor::OnZChanged ), NULL, this );
	
}

Vec2FloatEditor::Vec2FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer27->Add( m_name, 0, wxALL, 5 );
	
	m_x = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( m_x, 1, wxALL, 5 );
	
	m_y = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( m_y, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer27 );
	this->Layout();
	
	// Connect Events
	m_x->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec2FloatEditor::OnXChanged ), NULL, this );
	m_y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec2FloatEditor::OnYChanged ), NULL, this );
}

Vec2FloatEditor::~Vec2FloatEditor()
{
	// Disconnect Events
	m_x->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec2FloatEditor::OnXChanged ), NULL, this );
	m_y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec2FloatEditor::OnYChanged ), NULL, this );
	
}

QuatFloatEditor::QuatFloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer28->Add( m_name, 0, wxALL, 5 );
	
	m_w = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_w, 1, wxALL, 5 );
	
	m_x = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_x, 1, wxALL, 5 );
	
	m_y = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_y, 1, wxALL, 5 );
	
	m_z = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_z, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer28 );
	this->Layout();
	
	// Connect Events
	m_w->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnWChanged ), NULL, this );
	m_x->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnXChanged ), NULL, this );
	m_y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnYChanged ), NULL, this );
	m_z->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnZChanged ), NULL, this );
}

QuatFloatEditor::~QuatFloatEditor()
{
	// Disconnect Events
	m_w->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnWChanged ), NULL, this );
	m_x->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnXChanged ), NULL, this );
	m_y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnYChanged ), NULL, this );
	m_z->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuatFloatEditor::OnZChanged ), NULL, this );
	
}

FloatEditor::FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer29->Add( m_name, 0, wxALL, 5 );
	
	m_value = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_value, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer29 );
	this->Layout();
	
	// Connect Events
	m_value->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FloatEditor::OnValueChanged ), NULL, this );
}

FloatEditor::~FloatEditor()
{
	// Disconnect Events
	m_value->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FloatEditor::OnValueChanged ), NULL, this );
	
}

IntegerEditor::IntegerEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer30->Add( m_name, 0, wxALL, 5 );
	
	m_value = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( m_value, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer30 );
	this->Layout();
	
	// Connect Events
	m_value->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( IntegerEditor::OnValueChanged ), NULL, this );
}

IntegerEditor::~IntegerEditor()
{
	// Disconnect Events
	m_value->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( IntegerEditor::OnValueChanged ), NULL, this );
	
}

DoubleEditor::DoubleEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer31->Add( m_name, 0, wxALL, 5 );
	
	m_value = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_value, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer31 );
	this->Layout();
	
	// Connect Events
	m_value->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DoubleEditor::OnValueChanged ), NULL, this );
}

DoubleEditor::~DoubleEditor()
{
	// Disconnect Events
	m_value->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DoubleEditor::OnValueChanged ), NULL, this );
	
}

StringEditor::StringEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer32->Add( m_name, 0, wxALL, 5 );
	
	m_value = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_value, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer32 );
	this->Layout();
	
	// Connect Events
	m_value->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( StringEditor::OnValueChanged ), NULL, this );
}

StringEditor::~StringEditor()
{
	// Disconnect Events
	m_value->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( StringEditor::OnValueChanged ), NULL, this );
	
}

Vec4FloatEditor::Vec4FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer33->Add( m_name, 0, wxALL, 5 );
	
	m_x = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_x, 1, wxALL, 5 );
	
	m_y = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_y, 1, wxALL, 5 );
	
	m_z = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_z, 1, wxALL, 5 );
	
	m_w = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_w, 1, wxALL, 5 );
	
	
	this->SetSizer( bSizer33 );
	this->Layout();
	
	// Connect Events
	m_x->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnXChanged ), NULL, this );
	m_y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnYChanged ), NULL, this );
	m_z->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnZChanged ), NULL, this );
	m_w->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnWChanged ), NULL, this );
}

Vec4FloatEditor::~Vec4FloatEditor()
{
	// Disconnect Events
	m_x->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnXChanged ), NULL, this );
	m_y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnYChanged ), NULL, this );
	m_z->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnZChanged ), NULL, this );
	m_w->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Vec4FloatEditor::OnWChanged ), NULL, this );
	
}

Mat4FloatEditor::Mat4FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxVERTICAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer35->Add( m_name, 0, wxALL, 5 );
	
	
	bSizer34->Add( bSizer35, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxHORIZONTAL );
	
	m_0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_0, 1, wxALL|wxEXPAND, 5 );
	
	m_4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_4, 1, wxALL|wxEXPAND, 5 );
	
	m_8 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_8, 1, wxALL|wxEXPAND, 5 );
	
	m_12 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer37->Add( m_12, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer37, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	m_1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_1, 1, wxALL|wxEXPAND, 5 );
	
	m_5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_5, 1, wxALL|wxEXPAND, 5 );
	
	m_9 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_9, 1, wxALL|wxEXPAND, 5 );
	
	m_13 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_13, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer38, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );
	
	m_2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_2, 1, wxALL|wxEXPAND, 5 );
	
	m_6 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_6, 1, wxALL|wxEXPAND, 5 );
	
	m_10 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_10, 1, wxALL|wxEXPAND, 5 );
	
	m_14 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_14, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer39, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	m_3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_3, 1, wxALL|wxEXPAND, 5 );
	
	m_7 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_7, 1, wxALL|wxEXPAND, 5 );
	
	m_11 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_11, 1, wxALL|wxEXPAND, 5 );
	
	m_15 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_15, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer40, 1, wxEXPAND, 5 );
	
	
	bSizer34->Add( bSizer36, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer34 );
	this->Layout();
	
	// Connect Events
	m_0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On0Changed ), NULL, this );
	m_4->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On4Changed ), NULL, this );
	m_8->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On8Changed ), NULL, this );
	m_12->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On12Changed ), NULL, this );
	m_1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On1Changed ), NULL, this );
	m_5->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On5Changed ), NULL, this );
	m_9->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On9Changed ), NULL, this );
	m_13->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On13Changed ), NULL, this );
	m_2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On2Changed ), NULL, this );
	m_6->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On6Changed ), NULL, this );
	m_10->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On10Changed ), NULL, this );
	m_14->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On14Changed ), NULL, this );
	m_3->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On3Changed ), NULL, this );
	m_7->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On7Changed ), NULL, this );
	m_11->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On11Changed ), NULL, this );
	m_15->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On15Changed ), NULL, this );
}

Mat4FloatEditor::~Mat4FloatEditor()
{
	// Disconnect Events
	m_0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On0Changed ), NULL, this );
	m_4->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On4Changed ), NULL, this );
	m_8->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On8Changed ), NULL, this );
	m_12->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On12Changed ), NULL, this );
	m_1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On1Changed ), NULL, this );
	m_5->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On5Changed ), NULL, this );
	m_9->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On9Changed ), NULL, this );
	m_13->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On13Changed ), NULL, this );
	m_2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On2Changed ), NULL, this );
	m_6->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On6Changed ), NULL, this );
	m_10->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On10Changed ), NULL, this );
	m_14->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On14Changed ), NULL, this );
	m_3->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On3Changed ), NULL, this );
	m_7->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On7Changed ), NULL, this );
	m_11->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On11Changed ), NULL, this );
	m_15->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat4FloatEditor::On15Changed ), NULL, this );
	
}

Mat3FloatEditor::Mat3FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer42->Add( m_name, 0, wxALL, 5 );
	
	
	bSizer41->Add( bSizer42, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxHORIZONTAL );
	
	m_0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_0, 1, wxALL|wxEXPAND, 5 );
	
	m_3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_3, 1, wxALL|wxEXPAND, 5 );
	
	m_6 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer44->Add( m_6, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer43->Add( bSizer44, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );
	
	m_1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer45->Add( m_1, 1, wxALL|wxEXPAND, 5 );
	
	m_4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer45->Add( m_4, 1, wxALL|wxEXPAND, 5 );
	
	m_7 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer45->Add( m_7, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer43->Add( bSizer45, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );
	
	m_2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( m_2, 1, wxALL|wxEXPAND, 5 );
	
	m_5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( m_5, 1, wxALL|wxEXPAND, 5 );
	
	m_8 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( m_8, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer43->Add( bSizer46, 1, wxEXPAND, 5 );
	
	
	bSizer41->Add( bSizer43, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer41 );
	this->Layout();
	
	// Connect Events
	m_0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On0Changed ), NULL, this );
	m_3->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On3Changed ), NULL, this );
	m_6->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On6Changed ), NULL, this );
	m_1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On1Changed ), NULL, this );
	m_4->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On4Changed ), NULL, this );
	m_7->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On7Changed ), NULL, this );
	m_2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On2Changed ), NULL, this );
	m_5->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On5Changed ), NULL, this );
	m_8->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On8Changed ), NULL, this );
}

Mat3FloatEditor::~Mat3FloatEditor()
{
	// Disconnect Events
	m_0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On0Changed ), NULL, this );
	m_3->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On3Changed ), NULL, this );
	m_6->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On6Changed ), NULL, this );
	m_1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On1Changed ), NULL, this );
	m_4->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On4Changed ), NULL, this );
	m_7->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On7Changed ), NULL, this );
	m_2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On2Changed ), NULL, this );
	m_5->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On5Changed ), NULL, this );
	m_8->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat3FloatEditor::On8Changed ), NULL, this );
	
}

Mat2FloatEditor::Mat2FloatEditor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxVERTICAL );
	
	m_name = new wxStaticText( this, wxID_ANY, wxT("[NAME]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_name->Wrap( -1 );
	bSizer48->Add( m_name, 0, wxALL, 5 );
	
	
	bSizer47->Add( bSizer48, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );
	
	m_0 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_0, 1, wxALL|wxEXPAND, 5 );
	
	m_2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_2, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer49->Add( bSizer50, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	m_1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_1, 1, wxALL|wxEXPAND, 5 );
	
	m_3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_3, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer49->Add( bSizer51, 1, wxEXPAND, 5 );
	
	
	bSizer47->Add( bSizer49, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer47 );
	this->Layout();
	
	// Connect Events
	m_0->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On0Changed ), NULL, this );
	m_2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On2Changed ), NULL, this );
	m_1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On1Changed ), NULL, this );
	m_3->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On3Changed ), NULL, this );
}

Mat2FloatEditor::~Mat2FloatEditor()
{
	// Disconnect Events
	m_0->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On0Changed ), NULL, this );
	m_2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On2Changed ), NULL, this );
	m_1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On1Changed ), NULL, this );
	m_3->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Mat2FloatEditor::On3Changed ), NULL, this );
	
}
