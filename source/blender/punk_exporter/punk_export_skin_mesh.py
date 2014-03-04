import bpy
import copy
from copy import deepcopy

def export_skin_mesh(object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".skin"    
    print(file)
    f = open(file, "w")
    f.write("SKINMESHTEXT\n")
    skin = object.data
    start_block(f, skin.name)
    export_string(f, "*armature", object.parent.name)
    vertex_groups[object.data.name] = object.vertex_groups
    export_mat4(f, "*world_matrix", object.matrix_world)
    export_vertex_position(f, skin)
    export_normals(f, skin)
    export_faces(f, skin)
    export_tex_coords(f, skin)
    export_bones_weight(f, skin)
    if len(skin.materials) != 0:
        export_material(f, bpy.data.materials[skin.materials[0].name]) 
    end_block(f)    #   skin_mesh        
    f.close()        
    
    text_offset = old
    return
        
def export_skin_meshes(f): 
    if not ("*skin_mesh" in used_entities.keys()):
        return    
    for object in used_entities["*skin_mesh"]:
        data = object.data
        if data != None:
            export_skin_mesh(object)
    return

