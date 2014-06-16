from . import punk_export_base
from .punk_export_base import *
import bpy

def export_transform(object):
    export_location = punk_get_export_func("OBJECT.LOCATION")
    global text_offset
    old = text_offset
    text_offset = 0

    file = object.name + ".transform"
    print(file)
    f = open(file, "w")
    f.write("TRANSFORMTEXT\n")
    export_location(f, object)
    f.close()

    text_offset = old
    return

def export_transform_node(f, object):
    export_object = punk_get_export_func("OBJECT")
    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)
    for child in object.children:
        export_object(f, child)
    end_block(f) #  Transform
    return

def export_transforms(f):
    if not ("*transform" in used_entities.keys()):
        return
    for object in used_entities["*transform"]:
        export_transform(object)
    return

punk_register_export_func("TRANSFORM", export_transform_node)
punk_register_export_func("TRANSFORMS", export_transforms)
