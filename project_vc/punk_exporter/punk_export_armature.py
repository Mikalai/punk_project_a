from . import punk_export_base
from .punk_export_base import *

import bpy
import copy
from copy import deepcopy

#
#   used to export animation data
#
def export_action_ref(f, object):
    if object.animation_data == None:
        return
    animation = object.animation_data
    for track in animation.nla_tracks:        
        for strip in track.strips:
            export_string(f, "*action_ref", strip.name)
    return

#
#   export armature skeleton
#
def export_armature(object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".armature_schema"
    print(file)
    f = open(file, "w")
    f.write("ARMATURESCHEMATEXT\n")    
    armature = object.data
    start_block(f, armature.name)
    export_action_ref(f, object)
    for bone in armature.bones:
        #   export bone
        start_block(f, "*bone")
        #   export bone index
        export_int(f, "*index", armature.bones.find(bone.name))
        #   write bone name        
        export_string(f, "*name", bone.name)
        #   write bone length
        export_float(f, "*length", bone.length)
        #   write bone parent
        if bone.parent != None:
            export_string(f, "*parent", bone.parent.name)
        #   write bone matrix
        export_mat4(f, "*local_matrix", bone.matrix_local)
        #   write supported animation
        end_block(f)    #*bone
    end_block(f)    #*armature
    f.close()        

    file = object.data.name + ".armature"
    print(file)
    f = open(file, "w")
    f.write("ARMATURETEXT\n")    
    export_string(f, "*armature_schema", object.data.name + ".armature_schema")    
    f.close()        
        
    text_offset = old
    return

def export_armatures(f):
    if not ("*armature" in used_entities.keys()):
        return
    for object in used_entities["*armature"]:
        data = object.data
        if data != None:
            export_armature(object)
    return

def export_armature_node(f, object):
    export_object = punk_get_export_func("OBJECT")

    if object.data == None:
        return

    start_block(f, "*node")
    export_string(f, "*name", "Transform")
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)

    armature = object.data
    start_block(f, "*node")
    export_string(f, "*name", "Armature")
    export_string(f, "*entity_name", armature.name + ".armature")
    push_entity("*armature", object)

    for child in object.children:
        export_object(f, child)

    end_block(f)    #*armature_node
    end_block(f)    #*transform
    return

punk_register_export_func("HUMAN_ARMATURE", export_armature_node)
punk_register_export_func("ARMATURES", export_armatures)
