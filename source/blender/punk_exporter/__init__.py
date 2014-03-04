import bpy

# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####

# <pep8-80 compliant>

bl_info = {
    "name": "PunkEngine File Exporter",
    "author": "Mikalaj Abramau",
    "blender": (2, 57, 0),
    "location": "File > Import-Export",
    "description": "Export .pmd file format",
    "warning": "",    
    "tracker_url": "",    
    "category": "Import-Export"}

import os
PUNK_ENGINE_ROOT = os.environ.get('PUNK_ENGINE_ROOT')

if "bpy" in locals():
    import imp
    if "punk_export_base" in locals():
        imp.reload(punk_export_base)
    if "punk_export_terrain" in locals():
        imp.reload(punk_export_terrain)
    if "punk_export_model" in locals():
        imp.reload(punk_export_model)

def execfile(afile, globalz=None, localz=None):
    with open(afile, "r") as fh:
        exec(fh.read(), globalz, localz)
        
def include(filename):
    if os.path.exists(filename): 
        print("Loading " + filename)
        execfile(filename)
    else:
        print(filename + " doesn't exist")

import sys
sys.path.insert(0, PUNK_ENGINE_ROOT+"source/blender/punk_exporter")

import punk_export_base
import punk_export_model

from punk_export_model import *
#include(PUNK_ENGINE_ROOT+"source/blender/punk_exporter/punk_export_base.py")
#include(PUNK_ENGINE_ROOT+"source/blender/punk_exporter/punk_export_model.py")

import bpy
from bpy.props import StringProperty, FloatProperty, BoolProperty, EnumProperty

from bpy_extras.io_utils import (ImportHelper,
                                 ExportHelper,
                                 axis_conversion,
                                 )
	
class ExportPunkModel(bpy.types.Operator, ExportHelper):
    'Exports mesh for Punk Engine'
    bl_idname = "export.punk_model"  
    bl_label = "Export PunkEngine Scene"

    # ExportHelper Mixin classed uses this
    filename_ext = ".pmd"

    filter_glob = StringProperty(default="*.pmd", options = {'HIDDEN'})

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    export_animation = BoolProperty(name="Export animation", description="Export animation in separate .pan animation file", default=True)
    export_type = EnumProperty \
        (name = "Export type", description = "Define what output format is prefered", items = [ ("INDOOR_LOCATION", "Indoor location", "Indoor location", 1),\
               ("ARMATURE", "Armature", "Armature", 2), ("OUTDOOR_LOCATION", "Outdoor location", "Outdoor location") ])

    @classmethod
    def poll(cls, context):
        return context.active_object != None

    def execute(self, context):
        print("*** Punk Engine Blender Exporter ***")
        print(os.getcwd())
        print(os.environ.get('PUNK_ENGINE_ROOT'))
        return export_model(context, self.filepath, self.export_animation)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportPunkModel.bl_idname, text="Export Punk Model")


def register():
    bpy.utils.register_class(ExportPunkModel)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportPunkModel)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

bpy.ops.export.punk_model('INVOKE_DEFAULT')