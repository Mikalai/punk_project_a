if "bpy" in locals():
    import imp
    imp.reload(punk_export_base)
else:
    from . import punk_export_base
    from . import punk_export_static_mesh_node
    from . import punk_export_object
    from . import punk_export_static_mesh
    from . import punk_export_vertex_position
    from . import punk_export_faces
    from . import punk_export_face_normals
    from . import punk_export_normals
    from . import punk_export_texture_coords
    from . import punk_export_bones_weights
    from . import punk_export_skin_mesh
    from . import punk_export_skin_mesh_node
    from . import punk_export_transform
    from . import punk_export_material
    from . import punk_export_armature
    from . import punk_export_action

from .punk_export_base import *

import bpy
import os
import platform

#import punk_export_model

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
#from bpy_extras.io_utils import ExportHelper
#from bpy.props import StringProperty, BoolProperty, EnumProperty
#from punk_export_base import *

##   export local matrix
##
#def export_local_matrix(f, object):
#    start_block(f, "*local_matrix")
#    for v in object.matrix_local:
#        make_offset(f)
#        f.write('{0} {1} {2} {3}\n'.format(v[0], v[1], v[2], v[3]))
#    end_block(f)
#    return

##   export parent inverse matrix
##
#def export_parent_inverse_matrix(f, object):
#    start_block(f, "*parent_inverse_matrix")
#    for v in object.matrix_parent_inverse:
#        make_offset(f)
#        f.write("{0} {1} {2} {3}\n".format(v[0], v[1], v[2], v[3]))
#    end_block(f)
#    return

##
##   export mesh material
##
#def export_mesh_material(f, mesh):
#    if (mesh == None) or (len(mesh.materials) == 0):
#        return
#    start_block(f, "*material_ref")
#    make_offset(f)
#    f.write("%s\n" % mesh.materials[0].name)
#    used_materials.add(mesh.materials[0].name)
#    end_block(f)
#    return
  
##
##   export only mesh
##
##def export_mesh(f, object):
##    if object.data == None:
##        return
##    if type(object.data) == bpy.types.Mesh:
##        start_block(f, "*mesh")
##        export_vertex_position(f, object.data)
##        export_normals(f, object.data)
##        export_faces(f, object.data)
##        export_tex_coords(f, object.data)
##        export_mesh_material(f, object.data)
##        export_bones_weight(f, object)
##        end_block(f)
##    return

##
##   exort collision mesh
##
#def export_collision_mesh(f, object):
#    if object.data == None:
#        return
#    if type(object.data) == bpy.types.Mesh:
#        start_block(f, "*collision_mesh")
#        export_vertex_position(f, object.data)
#        end_block(f)
#    return
   
##
##   used to export animation data
##
##def export_action_ref(f, object):
##    if object.animation_data == None:
##        return
##    animation = object.animation_data
##    for track in animation.nla_tracks:
##        for strip in track.strips:
##            used_actions.add(strip.name)
##    return

##
##   export sound
##
#def export_sound(f, object):
#    start_block(f, "*sound")
#    export_string(f, "*name", object.data.name)
#    export_string(f, "*filename", object.data.sound.name)
#    export_float(f, "*volume", object.data.volume)
#    export_float(f, "*pitch", object.data.pitch)
#    export_float(f, "*max_distance", object.data.distance_max)
#    export_float(f, "*reference_distance", object.data.distance_reference)
#    export_float(f, "*cone_angle_inner", object.data.cone_angle_inner)
#    export_float(f, "*cone_angle_outer", object.data.cone_angle_outer)
#    export_float(f, "*cone_volume_outer", object.data.cone_volume_outer)
#    export_float(f, "*attenuation", object.data.attenuation)
#    end_block(f)    #   *sound
#    return

##
##   export properties
##
#def export_properties(f, object):
#    print(object.name)
#    try:
#        for p in object.items():
#            try:
#                print(p)
#                if p[0] == 'type':
#                    start_block(f, "*type")
#                    make_offset(f)
#                    f.write("%s\n" % p[1])
#                    end_block(f)
#                if p[0] == 'reference':
#                    export_string(f, "*reference", p[1])
#                if p[0] == 'subtype':
#                    export_string(f, "*subtype", p[1])
#                if p[0] == 'options':
#                    export_string(f, "*options", p[1])
#            except:
#                print("Bad property")
#    except:
#        print("No properties")
#    return
       
##
##   export animation tracks for the object
##
##def export_animation_tracks(f, object):
##    if object.animation_data == None:
##        return
##
##    if len(object.animation_data.nla_tracks) =override:
##        return
##
##    start_block(f, "*actions_ref")
##    for track in object.animation_data.nla_tracks:
##        if len(track.strips) =override:
##            print("No strips in track %s", track.name)
##            return
##        if len(track.strips) != 1:
##            print("Wanring: only first strip will be exported")
##       export_string(f, "*action_ref", track.strips[0].action.name)
##
##        used_actions.add(track.strips[0].action.name)
##
##    end_block(f)

#def export_light_node(f, object):
#    start_block(f, "*node")
#    export_string(f, "*name", object.name + "_transform")
#    export_object_matrix(f, object)
#    if type(object.data) == bpy.types.PointLamp:
#        push_entity("*point_lamp", object)
#        export_string(f, "*entity_name", object.data.name + ".point_lamp")
#    elif type(object.data) == bpy.types.SunLamp:
#        push_entity("*directional_lamp", object)
#        export_string(f, "*entity_name", object.data.name + ".dir_lamp")
#    elif type(object.data) == bpy.types.SpotLamp:
#        push_entity("*spot_lamp", object)
#        export_string(f, "*entity_name", object.data.name + ".spot_lamp")
#    end_block(f)
#    return
 
#def export_transform(f, object):
#    #   transform node can be bound to the bone, thus check this fact
#    if object.parent_bone != '':
#        start_block(f, "*bone_node")
#        export_string(f, "*name", object.parent_bone)
#    start_block(f, "*node")
#    export_string(f, "*name", object.name + "_transform")
#    export_children(f, object)
#    end_block(f)
#    if object.parent_bone != '':
#        end_block(f)    #*bone_node
#    return

#def export_portal(f, object):
#    if type(object.data) == bpy.types.Mesh:
#        start_block(f, "*node")
#        export_string(f, "*name", object.name + ".portal")
#        export_local_matrix(f, object)
#        export_vertex_position(f, object.data)
#        end_block(f)
#    return


#def export_convex_mesh(f, object):
#    if object.data == None:
#        return
#    if type(object.data) == bpy.types.Mesh:
#        start_block(f, "*convex_mesh")
#        export_vertex_position(f, object.data)
#        export_face_normals(f, object.data)
#        export_faces(f, object.data)
#        end_block(f)
#    return

#def export_sound_2d(f, object):
#    start_block(f, "*sound_2d")
#    export_common(f, object)
#    if type(object.data) == bpy.types.Speaker:
#        export_sound(f, object)
#    end_block(f)
#    return

#def export_sound_3d(f, object):
#    start_block(f, "*sound_3d")
#    export_common(f, object)
#    if type(object.data) == bpy.types.Speaker:
#        export_sound(f, object)
#    end_block(f)
#    return

#def export_character(f, object):
#    start_block(f, "*character")
#    export_common(f, object)
#    if type(object.data) == bpy.types.Armature:
#        export_armature(f, object.data)
#    export_children(f, object)
#    end_block(f)
#    return

#def export_location_indoor(f, object):
#    if type(object.data) == bpy.types.Mesh:
#        start_block(f, "*location_indoor")
#        export_local_matrix(f, object)
#        export_convex_mesh(f, object)
#        export_children(f, object)
#        end_block(f)
#    return

#def export_common(f, object):
#    export_properties(f, object)
#    export_name(f, object)
    
#    if object.parent != None:
#        export_string(f, "*parent", object.parent.name)
        
#    #export_bounding_box(f, object)
#    export_world_matrix(f, object)
#    export_local_matrix(f, object)
#    export_parent_inverse_matrix(f, object)
#    return

#def export_children(f, object):
#    for child in object.children:
#        export_object(f, child)
#    return
   
#def export_collision_mesh(f, object):
#    return

#def export_sun_node(f, object):
#    if object.data == None:
#        return
    
##    start_block(f, "*node")
    
##    export_string(f, "*name", object.name + "_transform")
##    export_object_matrix(f, object)
##    start_block(f, "*node")
##    export_string(f, "*name", object.data.name + ".sun")
##    end_block(f)    #   sun
##    end_block(f) #  transform
#    return

#def export_navi_mesh_node(f, object):
#    if object.data == None:
#        return
    
#    start_block(f, "*node")
    
#    export_string(f, "*name", object.name + "_transform")
#    export_local_matrix(f, object)
#    start_block(f, "*node")
#    export_string(f, "*name", object.data.name + ".navi_mesh")
#    push_entity("*navi_mesh", object)
#    export_children(f, object)
#    end_block(f)    #   sun
#    end_block(f) #  transform
#    return

#def export_terrain_node(f, object):
#    if object.data == None:
#        return
    
#    mesh = object.data
    
#    if not((mesh == None) or (len(mesh.materials) == 0)):
#        start_block(f, "*node")
#        push_entity("*material", mesh.materials[0])
#        export_string(f, "*name", mesh.materials[0].name + ".material")
    
#    start_block(f, "*node")
    
#    export_string(f, "*name", object.name + "_transform")
#    export_local_matrix(f, object)
#    start_block(f, "*node")
#    export_string(f, "*name", object.data.name + ".terrain")
#    push_entity("*terrain", object)
#    export_children(f, object)
#    end_block(f)    #   sun
#    end_block(f) #  transform
    
#    if not((mesh == None) or (len(mesh.materials) == 0)):
#        end_block(f)    #   material
#    return

#def export_river_node(f, object):
#    if object.data == None:
#        return
    
#    mesh = object.data
    
#    if not((mesh == None) or (len(mesh.materials) == 0)):
#        start_block(f, "*node")
#        push_entity("*material", mesh.materials[0])
#        export_string(f, "*name", mesh.materials[0].name + ".material")
    
#    start_block(f, "*node")
    
#    export_string(f, "*name", object.name + "_transform")
#    export_local_matrix(f, object)
#    start_block(f, "*node")
#    export_string(f, "*name", object.data.name + ".river")
#    push_entity("*river", object)
#    export_children(f, object)
#    end_block(f)    #   sun
#    end_block(f) #  transform
    
#    if not((mesh == None) or (len(mesh.materials) == 0)):
#        end_block(f)    #   material
#    return

#def export_path_node(f, object):
#    if object.data == None:
#        return
    
#    start_block(f, "*node")
    
#    export_string(f, "*name", object.name + "_transform")
#    export_local_matrix(f, object)
#    start_block(f, "*node")
#    export_string(f, "*name", object.data.name + ".path")
#    push_entity("*path", object)
#    export_children(f, object)
#    end_block(f)    #   path
#    end_block(f) #  transform
#    return

#def export_camera_node(f, object):
#    if object.data == None:
#       return
#    start_block(f, "*node")
#    export_string(f, "*name", object.name + "_transform")
#    export_local_matrix(f, object)
#    start_block(f, "*node")
#    export_string(f, "*name", object.data.name + ".camera")
#    push_entity("*camera", object)
#    export_children(f, object)
#    end_block(f) # camer
#    end_block(f) # transform
#    return


##
##   export the whole object with all data i can imagine
##

def export_model(context, filepath, anim_in_separate_file):
    print("Export scene")
    export_object = punk_get_export_func("OBJECT")
    export_static_meshes = punk_get_export_func("STATIC_MESHES")
    export_skin_meshes = punk_get_export_func("SKIN_MESHES")
    export_transforms = punk_get_export_func("TRANSFORMS")
    export_materials = punk_get_export_func("MATERIALS")
    export_armatures = punk_get_export_func("ARMATURES")
    export_actions = punk_get_export_func("ACTIONS")

    if export_object == None:
        return
    print(filepath)
    print(platform.system())
    if platform.system() == 'Windows':
        path = filepath.replace(filepath[filepath.rfind("\\"):], "")
    else:
        path = filepath.replace(filepath[filepath.rfind("/"):], "")
    print(path)
    cur_dir = os.getcwd()
    try:
        f = open(filepath, 'w')
        f.write("SCENETEXT\n")
        for obj in bpy.context.selected_objects:
            export_object(f, obj)
        os.chdir(path)
        export_static_meshes(f)
        export_skin_meshes(f)
        export_transforms(f)
        export_materials(f)
        export_actions(f)
        export_armatures(f)
#        export_suns(f)
#        export_navi_meshes(f)
#        export_terrains(f)
#        export_rivers(f)
#        export_paths(f)
#        export_cameras(f)
#        export_point_lamps(f)
#        export_dir_lamps(f)
        f.close()
        return {'FINISHED'}
    finally:
        os.chdir(path)
    
