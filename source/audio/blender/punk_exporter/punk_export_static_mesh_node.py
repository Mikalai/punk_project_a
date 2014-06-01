from . import punk_export_base
from .punk_export_base import *
import bpy

def punk_export_static_mesh_node(f, object):
    print("Export static mesh node")
    export_object = punk_get_export_func("OBJECT")
    export_location = punk_get_export_func("OBJECT.LOCATION")
    if export_object == None or export_location == None:
        return

    if object.data == None:
        return
    mesh = object.data
    if not((mesh == None) or (len(mesh.materials) == 0)):
        start_block(f, "*node")
        push_entity("*material", mesh.materials[0])
        export_string(f, "*name", mesh.materials[0].name)
        export_string(f, "*entity_name", mesh.materials[0].name + ".material")

    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)

    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*node")
        export_string(f, "*name", "Static")
        export_string(f, "*entity_name", object.data.name + ".static")
        push_entity("*static_mesh", object)
    if type(object.data) == bpy.types.Mesh:
        end_block(f)    # Static

    for child in object.children:
        export_object(f, child)    

    end_block(f) #  Transform

    if not((mesh == None) or (len(mesh.materials) == 0)):
        end_block(f)    #   material

    return

punk_register_export_func("STATIC", punk_export_static_mesh_node)
