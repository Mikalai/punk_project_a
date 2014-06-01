import bpy
import copy
from copy import deepcopy

def export_camera(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".camera"    
    f = open(file, "w")
    f.write("CAMERATEXT\n")
    
    camera = object.data
    start_block(f, "*camera")
    export_string(f, "*name", camera.name)
    export_string(f, "*type", camera.type)
    export_float(f, "*fov", camera.angle)
    export_float(f, "*near", camera.clip_start)
    export_float(f, "*far", camera.clip_end)
    export_float(f, "*focus", camera.dof_distance)
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

