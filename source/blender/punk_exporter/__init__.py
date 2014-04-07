bl_info = {
    "name": "PunkEngine File Exporter",
    "author": "Mikalaj Abramau",
    "blender": (2, 57, 0),
    "location": "File > Import-Export",
    "description": "Export .pmd file format",
    "warning": "",
    "tracker_url": "",
    "category": "Import-Export"}

if "bpy" in locals():
    import imp
    imp.reload(punk_export_base)
    imp.reload(punk_export_model)
else:
    from . import punk_export_base
    from . import punk_export_model

from .punk_export_model import *

import bpy
from bpy.props import StringProperty, FloatProperty, BoolProperty, EnumProperty
from bpy_extras.io_utils import (ImportHelper,
                                ExportHelper,
                                axis_conversion,
                                )
import os

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

#bpy.ops.export.punk_model('INVOKE_DEFAULT')
