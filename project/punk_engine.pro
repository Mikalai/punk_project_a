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
          punk_engine/punk_system \
          punk_engine/punk_image \
          punk_engine/punk_font \
          punk_engine/punk_terminal
          #punk_engine/punk_graphics

punk_string.depends = punk_error
punk_core.depends = punk_error punk_string
punk_math.depends = punk_error punk_string
punk_system.depends = punk_error punk_string punk_core
