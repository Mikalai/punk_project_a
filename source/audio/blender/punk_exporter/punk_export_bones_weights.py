import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

#
#   export bones weights
#
def export_bones_weight(f, data):    
    if len(vertex_groups) == 0:
        return
    
    start_block(f, "*bones_weight")    
    for vert in data.vertices:
        for group in vertex_groups[data.name]:
            try:
                ind = vert.index
                #print(ind)
                gr_name = group.name
                #print(gr_name)
                weight = group.weight(ind)
                #print(weight)
                make_offset(f)
                f.write("{0} {1} {2}\n".format(ind, gr_name, weight))
            except:
                pass
                #print("found a vertex that is not in a group")
    end_block(f)
    return

punk_register_export_func("BONES_WEIGHT", export_bones_weight)
