///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FORMS_H__
#define __FORMS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/ribbon/toolbar.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/control.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/combobox.h>
#include <wx/toolbar.h>
#include <wx/dataview.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////

namespace Punk
{
	namespace Engine
	{
		namespace Tools
		{
			#define ID_EDITOR_PANEL_MANAGER_TOGGLE_BOTTOM_PANEL 1000
			#define ID_EDITOR_TOGGLE_BOTTOM_PANEL 1001
			#define ID_EDITOR_TOGGLE_LOG 1002
			#define ID_EDITOR_TOGGLE_FULLSCREEN 1003
			#define ID_EDITOR_UNDO 1004
			#define ID_EDITOR_REDO 1005
			#define ID_ENGINE_MODULES_VIEW 1006
			#define ID_ENGINE_MODULES_LOAD 1007
			#define ID_ENGINE_MODULES_UNLOAD 1008
			#define ID_SCENE_LOAD 1009
			#define ID_SCENE_SAVE 1010
			#define ID_SCENE_ASSETS_LOAD 1011
			#define ID_SCENE_ASSETS_REMOVE 1012
			#define ID_SCENE_ASSETS_PROPERTY 1013
			#define ID_SCENE_NEW_SCENE 1014
			#define ID_SCENE_DELETE_SCENE 1015
			#define ID_SCENE_NEW_NODE 1016
			#define ID_SCENE_NODE_DELETE 1017
			#define ID_SCENE_PANEL 1018
			#define ID_SCENE_CURRENT_SCENE_CHANGED 1019
			#define ID_SCENE_SHOW_DETAILED_GRAPH 1020
			#define ID_SCENE_SHOW_OBJECTS_GRAPH 1021
			#define ID_SCENE_TREE_GRAPH 1022
			#define ID_CREATE_SCENE_OK 1023
			#define ID_ATTRIBUTE_CREATE_GROUP_CHANGED 1024
			#define ID_ATTRIBUTE_CREATE_LIST_CHANGED 1025
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class ModuleManagerDialog
			///////////////////////////////////////////////////////////////////////////////
			class ModuleManagerDialog : public wxDialog 
			{
				private:
				
				protected:
					wxListBox* m_loaded_modules_list;
					wxButton* m_add;
					wxButton* m_remove_module;
					wxStaticText* m_module_name;
					wxStaticText* m_name_value;
					wxStaticText* m_module_path;
					wxStaticText* m_module_path_value;
					wxButton* m_ok;
					
					// Virtual event handlers, overide them in your derived class
					void OnClose( wxCloseEvent& event );
					void OnInit( wxInitDialogEvent& event );
					void OnItemSelected( wxCommandEvent& event );
					void OnModuleAdd( wxCommandEvent& event );
					void OnModuleRemove( wxCommandEvent& event );
					void OnOk( wxCommandEvent& event );
					
				
				public:
					
					ModuleManagerDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Engine Modules"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
					~ModuleManagerDialog();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class SceneGraphPanel
			///////////////////////////////////////////////////////////////////////////////
			class SceneGraphPanel : public wxPanel 
			{
				private:
				
				protected:
				
				public:
					
					SceneGraphPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
					~SceneGraphPanel();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class EditorMainWindowBase
			///////////////////////////////////////////////////////////////////////////////
			class EditorMainWindowBase : public wxFrame 
			{
				private:
				
				protected:
					wxRibbonBar* m_scene_ribbon_bar;
					wxRibbonPage* m_editor_page;
					wxRibbonPanel* m_file_ribbon_panel;
					wxRibbonToolBar* m_file_toolbar;
					wxRibbonPanel* m_tools_manager;
					wxRibbonToolBar* m_panel_manager_toolbar;
					wxRibbonPanel* m_do_undo_panel;
					wxRibbonToolBar* m_do_undo_tool_bar;
					wxRibbonPage* m_engine_page;
					wxRibbonPanel* m_modules_panel;
					wxRibbonToolBar* m_module_toolbar;
					wxRibbonPage* m_scene_assets_page;
					wxRibbonPanel* m_scene_file_operations;
					wxRibbonToolBar* m_scene_file_operation_bar;
					wxRibbonPanel* m_assets_manager_panel;
					wxRibbonToolBar* m_assets_manager_toolbar;
					wxRibbonPanel* m_node_panel;
					wxRibbonToolBar* m_node_panel_bar;
					wxPanel* m_left_panel;
					wxNotebook* m_left_notebook;
					wxPanel* m_scene_panel;
					wxComboBox* m_scenes_combobox;
					wxToolBar* m_toolBar1;
					wxToolBarToolBase* m_detailed_graph; 
					wxToolBarToolBase* m_objects_graph; 
					wxDataViewTreeCtrl* m_scene_tree_graph;
					wxPanel* m_mid_panel;
					wxPanel* m_bottom_panel;
					wxNotebook* m_bottom_panel_stuff;
					wxPanel* m_log_panel;
					wxDataViewListCtrl* m_log;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnActivate( wxActivateEvent& event ) = 0;
					virtual void OnClose( wxCloseEvent& event ) = 0;
					virtual void OnIdle( wxIdleEvent& event ) = 0;
					virtual void OnToggleBottomPanel( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnToggleLog( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnToggleFullscreen( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnUndo( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnRedo( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnViewModules( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnLoadModule( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnUnloadModule( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneLoad( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneSave( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneCreate( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneDelete( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnNodeCreate( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnNodeDelete( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneChanged( wxCommandEvent& event ) = 0;
					virtual void OnSwitchDetailedGraph( wxCommandEvent& event ) = 0;
					virtual void OnSwitchObjectsGraph( wxCommandEvent& event ) = 0;
					virtual void OnSceneGraphItemActivated( wxDataViewEvent& event ) = 0;
					virtual void OnSceneDragBegin( wxDataViewEvent& event ) = 0;
					virtual void OnSceneContextMenu( wxDataViewEvent& event ) = 0;
					virtual void OnSceneDragDrop( wxDataViewEvent& event ) = 0;
					virtual void OnSceneCheckDrop( wxDataViewEvent& event ) = 0;
					virtual void OnSceneGraphItemChanged( wxDataViewEvent& event ) = 0;
					virtual void OnSize( wxSizeEvent& event ) = 0;
					
				
				public:
					
					EditorMainWindowBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Punk Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,840 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL );
					
					~EditorMainWindowBase();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class CreateSceneDialog
			///////////////////////////////////////////////////////////////////////////////
			class CreateSceneDialog : public wxDialog 
			{
				private:
				
				protected:
					wxTextCtrl* m_scene_name;
					wxButton* m_ok;
					wxButton* m_cancel;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					CreateSceneDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create scene"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
					~CreateSceneDialog();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class AttributePanel
			///////////////////////////////////////////////////////////////////////////////
			class AttributePanel : public wxPanel 
			{
				private:
				
				protected:
				
				public:
					wxBoxSizer* m_layout;
					
					AttributePanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 831,587 ), long style = wxTAB_TRAVERSAL ); 
					~AttributePanel();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class AttributeDialog
			///////////////////////////////////////////////////////////////////////////////
			class AttributeDialog : public wxDialog 
			{
				private:
				
				protected:
					wxComboBox* m_groups;
					wxListBox* m_attributes;
					wxStaticText* m_label_name;
					wxTextCtrl* m_attribute_name;
					wxButton* m_ok;
					wxButton* m_button6;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnGroupSelected( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnItemChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					wxStaticBoxSizer* m_parameters_sizer;
					
					AttributeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Select attribute"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 752,575 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER ); 
					~AttributeDialog();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class BooleanEditor
			///////////////////////////////////////////////////////////////////////////////
			class BooleanEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxCheckBox* m_check_box;
				
				public:
					
					BooleanEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 259,25 ), long style = wxTAB_TRAVERSAL ); 
					~BooleanEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Vec3FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Vec3FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_x;
					wxTextCtrl* m_y;
					wxTextCtrl* m_z;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnXChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnYChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnZChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Vec3FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 348,42 ), long style = wxTAB_TRAVERSAL ); 
					~Vec3FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Vec2FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Vec2FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_x;
					wxTextCtrl* m_y;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnXChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnYChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Vec2FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,41 ), long style = wxTAB_TRAVERSAL ); 
					~Vec2FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class QuatFloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class QuatFloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_w;
					wxTextCtrl* m_x;
					wxTextCtrl* m_y;
					wxTextCtrl* m_z;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnWChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnXChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnYChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnZChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					QuatFloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,46 ), long style = wxTAB_TRAVERSAL ); 
					~QuatFloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_value;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnValueChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,44 ), long style = wxTAB_TRAVERSAL ); 
					~FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class IntegerEditor
			///////////////////////////////////////////////////////////////////////////////
			class IntegerEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_value;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnValueChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					IntegerEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,45 ), long style = wxTAB_TRAVERSAL ); 
					~IntegerEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class DoubleEditor
			///////////////////////////////////////////////////////////////////////////////
			class DoubleEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_value;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnValueChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					DoubleEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,44 ), long style = wxTAB_TRAVERSAL ); 
					~DoubleEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class StringEditor
			///////////////////////////////////////////////////////////////////////////////
			class StringEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_value;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnValueChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					StringEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,37 ), long style = wxTAB_TRAVERSAL ); 
					~StringEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Vec4FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Vec4FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_x;
					wxTextCtrl* m_y;
					wxTextCtrl* m_z;
					wxTextCtrl* m_w;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnXChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnYChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnZChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnWChanged( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Vec4FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,46 ), long style = wxTAB_TRAVERSAL ); 
					~Vec4FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Mat4FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Mat4FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_0;
					wxTextCtrl* m_4;
					wxTextCtrl* m_8;
					wxTextCtrl* m_12;
					wxTextCtrl* m_1;
					wxTextCtrl* m_5;
					wxTextCtrl* m_9;
					wxTextCtrl* m_13;
					wxTextCtrl* m_2;
					wxTextCtrl* m_6;
					wxTextCtrl* m_10;
					wxTextCtrl* m_14;
					wxTextCtrl* m_3;
					wxTextCtrl* m_7;
					wxTextCtrl* m_11;
					wxTextCtrl* m_15;
					
					// Virtual event handlers, overide them in your derived class
					virtual void On0Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On4Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On8Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On12Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On1Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On5Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On9Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On13Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On2Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On6Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On10Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On14Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On3Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On7Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On11Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On15Changed( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Mat4FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 648,146 ), long style = wxTAB_TRAVERSAL ); 
					~Mat4FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Mat3FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Mat3FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_0;
					wxTextCtrl* m_3;
					wxTextCtrl* m_6;
					wxTextCtrl* m_1;
					wxTextCtrl* m_4;
					wxTextCtrl* m_7;
					wxTextCtrl* m_2;
					wxTextCtrl* m_5;
					wxTextCtrl* m_8;
					
					// Virtual event handlers, overide them in your derived class
					virtual void On0Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On3Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On6Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On1Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On4Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On7Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On2Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On5Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On8Changed( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Mat3FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,113 ), long style = wxTAB_TRAVERSAL ); 
					~Mat3FloatEditor();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class Mat2FloatEditor
			///////////////////////////////////////////////////////////////////////////////
			class Mat2FloatEditor : public wxPanel 
			{
				private:
				
				protected:
					wxStaticText* m_name;
					wxTextCtrl* m_0;
					wxTextCtrl* m_2;
					wxTextCtrl* m_1;
					wxTextCtrl* m_3;
					
					// Virtual event handlers, overide them in your derived class
					virtual void On0Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On2Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On1Changed( wxCommandEvent& event ) { event.Skip(); }
					virtual void On3Changed( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					Mat2FloatEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,80 ), long style = wxTAB_TRAVERSAL ); 
					~Mat2FloatEditor();
				
			};
			
		} // namespace Tools
	} // namespace Engine
} // namespace Punk

#endif //__FORMS_H__
