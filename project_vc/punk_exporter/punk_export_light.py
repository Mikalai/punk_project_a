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
    file = object.name + ".point_light"
    print(file)
    f = open(file, "w")
    f.write("POINTLIGHTTEXT\n") 
    lamp = object.data        
    start_block(f, lamp.name)
    export_string(f, "*name", lamp.name)
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
    print("Export *point_light")
    if not ("*point_light" in used_entities.keys()):
        return
    for object in used_entities["*point_light"]:
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
    f.write("DIRLIGHTTEXT\n") 
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
    print("Export *directional_light")
    if not ("*directional_light" in used_entities.keys()):
        return
    for object in used_entities["*directional_light"]:
        data = object.data
        if data != None:
            export_directional_light(object)
    return

punk_register_export_func("DIRECTIONAL_LIGHTS", export_dir_lamps)
punk_register_export_func("POINT_LIGHTS", export_point_lamps)