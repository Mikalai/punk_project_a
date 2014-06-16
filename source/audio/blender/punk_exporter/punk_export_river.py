import bpy
import copy
from copy import deepcopy

def export_river(f, object):
    export_static_mesh(f, object)
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".river"    
    f = open(file, "w")
    f.write("RIVERTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    export_string(f, "*mesh", mesh.name + ".static")    
    export_float(f, "*flow_speed", 1)
    export_vec3(f, "*flow_direction", [1, 0, 0])
    end_block(f)    #   river            
    f.close()        
    
    text_offset = old    
    return
    
def export_rivers(f): 
    if not ("*river" in used_entities.keys()):
        return    
    for object in used_entities["*river"]:
        data = object.data
        if data != None:
            export_river(f, object)
    return

