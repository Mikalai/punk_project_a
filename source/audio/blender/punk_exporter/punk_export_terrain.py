import bpy
import copy
import punk_export_base
from punk_export_base import *
from copy import deepcopy

def export_terrain(f, object):    
    global text_offset
    old = text_offset 
    text_offset = 0

    scene = object.users_scene[0]
    scene.render.image_settings.file_format = 'TIFF'
    scene.render.image_settings.color_mode = 'BW'
    scene.render.image_settings.color_depth = '16'
    scene.render.filepath =
    
    file = object.data.name + ".terrain"    
    f = open(file, "w")
    f.write("TERRAINTEXT\n")    
    mesh = object.data
    start_block(f, mesh.name)
    export_string(f, "*mesh", mesh.name + ".static")
    end_block(f)    #   terrain        
    f.close()        
    
    text_offset = old    
    return
    
def export_terrains(f): 
    if not ("*terrain" in used_entities.keys()):
        return    
    for object in used_entities["*terrain"]:
        data = object.data
        if data != None:
            export_terrain(f, object)
    return

