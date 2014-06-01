import bpy
import copy
from copy import deepcopy

def export_suns(f):
    if not ("*sun" in used_entities.keys()):
        return
    
    for object in used_entities["*sun"]:
        data = object.data
        if data != None:
            export_sun(f, object)
    return

def export_sun(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".sun"    
    f = open(file, "w")
    f.write("SUNTEXT\n")
    sun = object.data
    start_block(f, sun.name)
    export_float(f, "*energy", sun.energy)
    export_vec3(f, "*color", sun.color)
    end_block(f)    #   skin_mesh        
    f.close()
    
    text_offset = old    
    return
