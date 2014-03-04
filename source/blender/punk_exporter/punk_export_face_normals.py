import bpy
import copy
from copy import deepcopy

#
#   eports face normals
#
def export_face_normals(f, mesh):
    if (mesh == None) or len(mesh.polygons) == 0:
        return
    start_block(f, "*face_normals")
    for face in mesh.polygons:
        make_offset(f)
        f.write("{0} {1} {2} {3}\n".format(face.index, face.normal[0], face.normal[1], face.normal[2]))
    end_block(f)
    return

