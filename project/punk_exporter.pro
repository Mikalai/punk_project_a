######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

TEMPLATE = subdirs
CONFIG += ordered
CONFIG -= QT

SUBDIRS = punk_engine/punk_error \
          punk_engine/punk_string \
          punk_engine/punk_math \
          punk_engine/punk_core \
          punk_engine/punk_terminal \
          punk_engine/punk_system \
          punk_engine/punk_image \                   
          punk_engine/punk_font \
          punk_engine/punk_graphics \
		  punk_engine/punk_scene \
		  punk_engine/punk_attributes \
		  punk_engine/punk_loader \		  
          #punk_engine/punk_gui \
          #punk_engine/punk_physics \          
          #tower_defense

punk_string.depends = punk_error
punk_core.depends = punk_error punk_string
punk_math.depends = punk_error punk_string
punk_terminal.depends = punk_error punk_string punk_core
punk_system.depends = punk_error punk_string punk_core
punk_font.depends = punk_system punk_error punk_string punk_core
punk_image.depends = punk_error punk_string punk_system
punk_gui.depends = punk_error punk_string punk_system punk_core punk_image punk_math
punk_physics = punk_error punk_string punk_core punk_math
punk_scene = punk_string punk_core punk_math punk_system punk_font punk_image
punk_attributes = punk_string punk_core punk_math punk_system punk_font punk_image punk_scene
punk_loader = punk_string punk_core punk_math punk_system punk_font punk_image punk_scene punk_attributes
