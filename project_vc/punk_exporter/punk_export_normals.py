import bpy
import copy
from . import punk_export_base
from .punk_export_base import *

from copy import deepcopy

#
#   export normalse. one normal for one vertex. i still don't know
#   how to realize when one vertex can have some normals depending
#   on the current face
#   
def export_normals(f, mesh):
    if len(mesh.vertices) == 0:
        return;
    
    start_block(f, "*normals")
    #make_offset(f)
    #   f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("{0} {1} {2}\n".format(vertex.normal.x, vertex.normal.y, vertex.normal.z))
    end_block(f)
    return
    
punk_register_export_func("NORMALS", export_normals)
