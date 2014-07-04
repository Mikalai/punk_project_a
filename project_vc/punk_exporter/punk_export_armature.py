from . import punk_export_base
from .punk_export_base import *

import bpy
import mathutils
import copy
from copy import deepcopy

#
#   used to export animation data
#
def export_action_ref(f, object):
    print("Export action ref")
    if object.animation_data == None:
        print("Animation data is empty")
        return
    animation = object.animation_data
    for track in animation.nla_tracks:        
        for strip in track.strips:
            export_string(f, "*action_ref", strip.action.name)
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
    pose = object.pose
    armature = object.data
    start_block(f, armature.name)
    if object.animation_data != None:
        animation = object.animation_data
        for track in animation.nla_tracks:        
            for strip in track.strips:
                export_string(f, "*action_ref", strip.action.name)
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
        parent_matrix = object.matrix_local
        if bone.parent != None:
            parent_matrix = armature.bones[bone.parent.name].matrix_local
            export_string(f, "*parent", armature.bones.find(bone.parent.name))
        #   write bone local position
        m = (parent_matrix.inverted() * bone.matrix_local).inverted()
        export_vec3(f, "*position", m.to_translation())
        #   write bone local rotation
        export_quat(f, "*rotation", m.to_quaternion())
        #   write supported animation
        end_block(f)    #*bone
    end_block(f)    #*armature
    f.close()        

    file = object.name + ".armature"
    print(file)
    f = open(file, "w")
    f.write("ARMATURETEXT\n")    
    start_block(f, object.name)
    export_string(f, "*armature_schema", object.data.name + ".armature_schema")    
    end_block(f)
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
    export_string(f, "*entity_name", object.name + ".armature")
    push_entity("*armature", object)

    for child in object.children:
        export_object(f, child)

    end_block(f)    #*armature_node
    end_block(f)    #*transform
    return

punk_register_export_func("HUMAN_ARMATURE", export_armature_node)
punk_register_export_func("ARMATURES", export_armatures)
