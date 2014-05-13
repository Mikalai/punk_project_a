import bpy
import copy
from copy import deepcopy
from . import punk_export_base
from .punk_export_base import *

#
#   export tex coords. i can't understand what is uv1 uv2 uv3 uv4
#   but i export all this staff. later should clear situation
#
def export_tex_coords(f, mesh):
    
    if (mesh == None) or (len(mesh.uv_textures) == 0):
        return

    index = 0;
    for texture in mesh.uv_layers:
        start_block(f, "*texture")    
        start_block(f, "*name")
        make_offset(f)
        f.write("%d\n" % index)
        index = index + 1
        end_block(f)
        
        start_block(f, "*tex_coord")        
        #
        #   uv1 uv2 uv3 uv4
        #

        data = texture.data
    
        for face in range(0, len(mesh.polygons)):
            make_offset(f)
            f.write("{0} {1} {2} {3} {4} {5}\n".format(data[3*face].uv[0], data[3*face].uv[1], data[3*face+1].uv[0], data[3*face+1].uv[1], data[3*face+2].uv[0], data[3*face+2].uv[1]))
            
        end_block(f)   
        end_block(f)
    return

punk_register_export_func("TEXTURE_COORDS", export_tex_coords)
