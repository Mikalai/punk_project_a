import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

def export_skin_mesh(object):
    export_vertex_position = punk_get_export_func("VERTEX_POSITION")
    export_normals = punk_get_export_func("NORMALS")
    export_faces = punk_get_export_func("FACES")
    export_tex_coords = punk_get_export_func("TEXTURE_COORDS")
    export_bones_weight = punk_get_export_func("BONES_WEIGHT")

    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".skin"    
    print(file)
    f = open(file, "w")
    f.write("SKINMESHTEXT\n")
    skin = object.data
    start_block(f, skin.name)
    export_string(f, "*armature_schema", object.parent.name)    
    export_mat4(f, "*armature_matrix", object.matrix_local)
    export_vertex_position(f, skin)
    export_normals(f, skin)
    export_faces(f, skin)
    export_tex_coords(f, skin)
    export_bones_weight(f, object)
    #if len(skin.materials) != 0:
    #    export_material(f, bpy.data.materials[skin.materials[0].name])
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

punk_register_export_func("SKIN_MESH", export_skin_mesh)
punk_register_export_func("SKIN_MESHES", export_skin_meshes)


def export_skin_mesh_node(f, object):
    print("Export skin mesh node")
    export_object = punk_get_export_func("OBJECT")
    export_location = punk_get_export_func("OBJECT.LOCATION")
    if export_object == None or export_location == None:
        return

    if object.data == None:
        return
    mesh = object.data
    if not((mesh == None) or (len(mesh.materials) == 0)):
        start_block(f, "*node")
        push_entity("*material", mesh.materials[0])
        export_string(f, "*name", "Material")
        export_string(f, "*entity_name", mesh.materials[0].name + ".material")

    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)

    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*node")
        export_string(f, "*name", "Skin")
        export_string(f, "*entity_name", object.data.name + ".skin")
        push_entity("*skin_mesh", object)
    for child in object.children:
        export_object(f, child)

    if type(object.data) == bpy.types.Mesh:
        end_block(f)    # Skin
    end_block(f) #  Transform

    if not((mesh == None) or (len(mesh.materials) == 0)):
        end_block(f)    #   material

    return

punk_register_export_func("SKIN", export_skin_mesh_node)
