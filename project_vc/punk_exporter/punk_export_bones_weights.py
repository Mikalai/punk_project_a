import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

#
#   export bones weights
#
def export_bones_weight(f, object):    
    if len(object.vertex_groups) == 0:
        return
    
    data = object.data

    start_block(f, "*bones_weights")    
    for vert in data.vertices:
        weight_map = {}
        for group in object.vertex_groups:
            try:                
                armature = object.parent.data
                group_name = group.name
                bone_index = armature.bones.find(group_name)
                ind = vert.index
                #print(ind)
                gr_name = group.name
                #print(gr_name)
                weight = group.weight(ind)
                weight_map[bone_index] = weight
                #print(weight)                
            except:
                pass
                #print("found a vertex that is not in a group")        
        start_block(f, "*vertex_bones_weights");
        export_int(f, "*vertex_index", vert.index)
        start_block(f, "*weights");
        for bone_id, weight in weight_map.items():
            make_offset(f);
            f.write("{0} {1}\n".format(bone_id, weight))
        end_block(f)
        end_block(f)
    end_block(f)
    return

punk_register_export_func("BONES_WEIGHT", export_bones_weight)
