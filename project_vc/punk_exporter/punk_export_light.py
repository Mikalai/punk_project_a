from . import punk_export_base
from .punk_export_base import *

import bpy
import copy
from copy import deepcopy

#
#   export lamps from the scene
#
def export_point_lamp(object):
    global text_offset
    old = text_offset 
    text_offset = 0
    file = object.data.name + ".point_lamp"
    print(file)
    f = open(file, "w")
    f.write("POINTLAMPTEXT\n") 
    lamp = object.data        
    start_block(f, lamp.name)
    export_vec3(f, "*color", lamp.color)
    export_float(f, "*distance", lamp.distance)
    export_float(f, "*energy", lamp.energy)
    export_float(f, "*linear_attenuation", lamp.linear_attenuation)
    export_float(f, "*quadratic_attenuation", lamp.quadratic_attenuation)
    end_block(f);
    f.close()            
    text_offset = old
    return
         
         
def export_point_lamps(f):
    print("Export *point_lamp")
    if not ("*point_lamp" in used_entities.keys()):
        return
    for object in used_entities["*point_lamp"]:
        data = object.data
        if data != None:
            export_point_lamp(object)
    return

def export_directional_light(object):
    global text_offset
    old = text_offset 
    text_offset = 0
    file = object.data.name + ".directional_light"
    print(file)
    f = open(file, "w")
    f.write("DIRLAMPTEXT\n") 
    lamp = object.data        
    start_block(f, lamp.name)
    export_vec3(f, "*color", lamp.color)
    export_float(f, "*distance", lamp.distance)
    export_float(f, "*energy", lamp.energy)
    export_vec3(f, "*direction", [0, 0, 1])
    end_block(f);
    f.close()            
    text_offset = old
    return

def export_dir_lamps(f):
    print("Export *directional_lamp")
    if not ("*directional_lamp" in used_entities.keys()):
        return
    for object in used_entities["*directional_lamp"]:
        data = object.data
        if data != None:
            export_directional_light(object)
    return

punk_register_export_func("DIRECTIONAL_LIGHTS", export_dir_lamps)
punk_register_export_func("POINT_LIGHTS", export_point_lamps)