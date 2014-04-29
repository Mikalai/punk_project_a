import bpy
import copy
import punk_export_base
from punk_export_base import *
from copy import deepcopy

def export_bounding_box(f, object):
    start_block(f, "*bounding_box")
        
    for vertex in object.bound_box:
        make_offset(f)
        f.write("{0} {1} {2}\n".format(vertex[0], vertex[1], vertex[2]))
    
    end_block(f)
    return
