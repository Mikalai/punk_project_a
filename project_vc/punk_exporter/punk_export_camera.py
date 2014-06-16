from . import punk_export_base
from .punk_export_base import *

import bpy
import mathutils
import copy
from copy import deepcopy

def export_camera_node(f, object):
    print("Export camera node")
    export_object = punk_get_export_func("OBJECT")
    export_location = punk_get_export_func("OBJECT.LOCATION")
    if export_object == None or export_location == None:
        return

    if object.data == None:
        return
    camera = object.data    

    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)
    
    start_block(f, "*node")
    export_string(f, "*name", "Camera")
    if (camera.type == "PERSP"):
        export_string(f, "*entity_name", object.data.name + ".perspective_camera")
    elif (camera.type == "ORTHO"):
        export_string(f, "*entity_name", object.data.name + ".ortho_camera")
    elif (camera.type == "PANO"):
        export_string(f, "*entity_name", object.data.name + ".panoramic_camera")

    push_entity("*camera", object)

    for child in object.children:
        export_object(f, child)

    end_block(f)    # Path
    end_block(f) #  Transform    

    return

def export_camera(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0

    camera = object.data    

    file = object.data.name + ".perspective_camera"    
    f = open(file, "w")
    f.write("CAMERATEXT\n")        
       
    if (camera.type == "PERSP"):
        start_block(f, "*perspective_camera")
    elif (camera.type == "ORTHO"):
        start_block(f, "*ortho_camera")
    elif (camera.type == "PANO"):
        start_block(f, "*panoramic_camera")
    
    export_string(f, "*name", camera.name)    
    export_float(f, "*fov", camera.angle)
    export_float(f, "*near", camera.clip_start)
    export_float(f, "*far", camera.clip_end)
    export_float(f, "*focus", camera.dof_distance)
    export_vec3(f, "*up_vector", [0, 0, 1])

    if (camera.type == "ORTHO"):
        export_float(f, "*ortho_scale", camera.ortho_scale)   
    end_block(f)
    
    f.close()        
    
    text_offset = old    
    return

def export_cameras(f):
    if not ("*camera" in used_entities.keys()):
        return
    for object in used_entities["*camera"]:
        data = object.data
        if data != None:
            export_camera(f, object)
    return

punk_register_export_func("CAMERA", export_camera_node)
punk_register_export_func("CAMERAS", export_cameras)
