import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

#
#   export vertex id for faces. it is practicaly enough. but
#   it is needed more info later. 
#
def export_faces(f, mesh):
    
    if (mesh == None) or len(mesh.polygons) == 0:
        return
    
    start_block(f, "*faces")
    for face in mesh.polygons:
        make_offset(f)
        f.write("{0} {1} {2}\n".format(face.vertices[0], face.vertices[1], face.vertices[2]))
    end_block(f)
    
    return

punk_register_export_func("FACES", export_faces)
