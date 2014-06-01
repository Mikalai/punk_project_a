import bpy
import copy
from copy import deepcopy

def export_navi_mesh(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".navi_mesh"    
    print("Export static mesh to " + file)
    f = open(file, "w")
    f.write("NAVIMESHTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    export_mat4(f, "*world_matrix", object.matrix_world)
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    end_block(f)    #   skin_mesh        
    f.close()        
    
    text_offset = old    
    return
    
def export_navi_meshes(f): 
    if not ("*navi_mesh" in used_entities.keys()):
        return    
    for object in used_entities["*navi_mesh"]:
        data = object.data
        if data != None:
            export_navi_mesh(f, object)
    return

