import bpy
import copy
from copy import deepcopy

def export_texture_slot(f, slot):
    start_block(f, "*texture_slot")
    try:
        export_vec3(f, "*scale", slot.scale)
        s = slot.texture.image.filepath
        export_string(f, "*image", s[s.rfind('/')+1:])
        if slot.use_map_color_diffuse:
            export_float(f, "*diffuse_map", slot.diffuse_color_factor)   
        if slot.use_map_normal:
            export_float(f, "*normal_map", slot.normal_factor)
        if slot.use_map_specular:
            export_float(f, "*specular_intensity_map", slot.specular_factor)
        end_block(f)    #*texture
    except:
        print("Failed to export texture")
    return
