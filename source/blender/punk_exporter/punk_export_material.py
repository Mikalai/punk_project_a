import bpy
import copy
from copy import deepcopy

def export_material(f, m):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = m.name + ".material"
    print(file)
    f = open(file, "w")
    f.write("MATERIALTEXT\n")
    start_block(f, m.name)
    export_float(f, "*alpha", m.alpha)
    export_float(f, "*ambient", m.ambient)
    export_float(f, "*darkness", m.darkness)
    export_vec3(f, "*diffuse_color", m.diffuse_color)
    export_float(f, "*diffuse_fresnel", m.diffuse_fresnel)
    export_float(f, "*diffuse_fresnel_factor", m.diffuse_fresnel_factor)
    export_float(f, "*diffuse_intensity", m.diffuse_intensity)
    export_float(f, "*emit", m.emit)
    export_vec3(f, "*mirror_color", m.mirror_color)
    export_float(f, "*roughness", m.roughness)
    export_float(f, "*specular_alpha", m.specular_alpha)
    export_vec3(f, "*specular_color", m.specular_color)
    export_float(f, "*specular_hardness", m.specular_hardness)
    export_float(f, "*specular_intensity", m.specular_intensity)
    export_float(f, "*specular_ior", m.specular_ior)
    export_float(f, "*specular_slope", m.specular_slope)
    export_float(f, "*translucency", m.translucency)

    for slot in m.texture_slots:
        try:            
            if slot.texture.image != None:
                export_texture_slot(f, slot)
        except:
            print("No texture found")
                        
    end_block(f)  # *material
    f.close()        
    
    text_offset = old  
    return 

#   export all materials
def export_materials(f):
    if not ("*material" in used_entities.keys()):
        return        
    for material in used_entities["*material"]:
        if material != None:
            export_material(f, material)
    return
