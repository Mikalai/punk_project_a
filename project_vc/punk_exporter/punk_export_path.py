from . import punk_export_base
from .punk_export_base import *

import bpy
import copy
from copy import deepcopy

def export_path(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".path"    
    f = open(file, "w")
    f.write("PATHTEXT\n")
    curve = object.data    
    start_block(f, curve.name)
    for spline in curve.splines:
        start_block(f, "*spline")
        for point in spline.points:
            start_block(f, "*point")
            export_float(f, "*weight", point.weight)
            export_vec4(f, "*position", point.co)
            end_block(f)
        end_block(f)
    end_block(f)    #   path
    f.close()        
    
    text_offset = old    
    return
    
def export_paths(f): 
    if not ("*path" in used_entities.keys()):
        return    
    for object in used_entities["*path"]:
        data = object.data
        if data != None:
            export_path(f, object)
    return

punk_register_export_func("PATHS", export_paths)