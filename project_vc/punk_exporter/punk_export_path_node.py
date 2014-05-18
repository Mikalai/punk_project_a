from . import punk_export_base
from .punk_export_base import *
import bpy

def export_path_node(f, object):
    print("Export path node")
    export_object = punk_get_export_func("OBJECT")
    export_location = punk_get_export_func("OBJECT.LOCATION")
    if export_object == None or export_location == None:
        return

    if object.data == None:
        return
    mesh = object.data    

    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)
    
    start_block(f, "*node")
    export_string(f, "*name", "Path")
    export_string(f, "*entity_name", object.data.name + ".path")
    push_entity("*path", object)

    for child in object.children:
        export_object(f, child)

    end_block(f)    # Path
    end_block(f) #  Transform    

    return

punk_register_export_func("PATH", export_path_node)
