from . import punk_export_base
from .punk_export_base import *

import bpy
import copy
from copy import deepcopy
import os
import platform

def export_texture_slot(f, slot):
    
    if slot.use_map_color_diffuse:
        start_block(f, "*diffuse_texture_slot")
    elif slot.use_map_normal:
        start_block(f, "*normal_texture_slot")
    elif slot.use_map_specular:
        start_block(f, "*specular_texture_slot")
    else:
        raise Exception("Unsupported texture slot")
    try:
        export_vec3(f, "*scale", slot.scale)
        s = slot.texture.image.filepath
        if platform.system() == 'Windows':
            export_string(f, "*image", s[s.rfind('\\')+1:])
        else:
            export_string(f, "*image", s[s.rfind('/')+1:])
        if slot.use_map_color_diffuse:
            factor = slot.diffuse_color_factor
        if slot.use_map_normal:
            factor = slot.normal_factor
        if slot.use_map_specular:
            factor = slot.specular_factor
        export_float(f, "*factor", factor)   
        end_block(f)    #*texture
    except:
        print("Failed to export texture")
    return

punk_register_export_func("TEXTURE_SLOT", export_texture_slot)