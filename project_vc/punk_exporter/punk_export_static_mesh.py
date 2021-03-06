import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

def export_static_mesh(f, object):
    export_vertex_position = punk_get_export_func("VERTEX_POSITION")
    export_normals = punk_get_export_func("NORMALS")
    export_faces = punk_get_export_func("FACES")
    export_tex_coords = punk_get_export_func("TEXTURE_COORDS")

    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".static"    
    print("Export static mesh to " + file)
    f = open(file, "w")
    f.write("STATICMESHTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    #export_mat4(f, "*world_matrix", object.matrix_world)
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    export_tex_coords(f, mesh)
#    if len(mesh.materials) != 0:
#        export_material(f, bpy.data.materials[mesh.materials[0].name])
    end_block(f)    #   static_mesh
    f.close()        
    
    text_offset = old    
    return
    
def export_static_meshes(f): 
    if not ("*static_mesh" in used_entities.keys()):
        return    
    for object in used_entities["*static_mesh"]:
        data = object.data
        if data != None:
            export_static_mesh(f, object)
    return

punk_register_export_func("STATIC_MESH", export_static_mesh)
punk_register_export_func("STATIC_MESHES", export_static_meshes)
