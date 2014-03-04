import bpy
import copy
from copy import deepcopy
   
#
#   exports vertex position for current mesh with no tranformation
#   applied in the scene
#
def export_vertex_position(f, mesh):   
    if (mesh == None) or (len(mesh.vertices) == 0):
        return
    start_block(f, "*vertex_position")    
    #f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("{0} {1} {2} {3}\n".format(vertex.index, vertex.co.x, vertex.co.y, vertex.co.z))

    end_block(f)
    return

