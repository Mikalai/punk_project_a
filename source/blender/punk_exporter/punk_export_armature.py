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
    
    file = object.data.name + ".armature"
    print(file)
    f = open(file, "w")
    f.write("ARMATURETEXT\n")    
    armature = object.data
    start_block(f, armature.name)
    export_action_ref(f, object)
    for bone in armature.bones:
        #   export bone
        start_block(f, "*bone")
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

