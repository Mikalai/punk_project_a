from . import punk_export_base

from .punk_export_base import *

def export_object_location(f, object):
    m = object.matrix_local
    p = m.to_translation()
    r = m.to_quaternion()
    s = m.to_scale()
    export_vec3(f, "*location", p)
    export_quat(f, "*rotation", r)
    export_vec3(f, "*scale", object.scale)
    return

def export_object(f, object):
    print("Export object: " + object.name + "(" + type(object).__name__ + ")")
    try:
        export = punk_get_export_func(object.punk_entity_type)
        if (export == None):
            return
        export(f, object)
    except:
        export = None
    return

punk_register_export_func("OBJECT", export_object)
punk_register_export_func("OBJECT.LOCATION", export_object_location)

#    if object.punk_entity_type == "LOCATION_INDOOR":
#        export_location_indoor(f, object)
#    elif object.punk_entity_type == "TRANSFORM":
#        export_transform(f, object)
#    elif object.punk_entity_type == "SUN":
#        export_sun_node(f, object)
#    elif object.punk_entity_type == "TERRAIN":
#        export_terrain_node(f, object)
#    elif object.punk_entity_type == "RIVER":
#        export_river_node(f, object)
#    elif object.punk_entity_type == "PATH":
#        export_path_node(f, object)
#    elif object.punk_entity_type == "HUMAN_ARMATURE":
#        export_armature_node(f, object)
#    elif object.punk_entity_type == "LIGHT":
#        export_light_node(f, object)
#    elif object.punk_entity_type == "PORTAL":
#        export_portal(f, object)
#    elif object.punk_entity_type == "STATIC":
#        export_static_mesh_node(f, object)
#    elif object.punk_entity_type == "SKIN":
#        export_skin_mesh_node(f, object)
#    elif object.punk_entity_type == "NAVI":
#        export_navi_mesh_node(f, object)
#    elif object.punk_entity_type == "SOUND_2D":
#        export_sound_2d(f, object)
#    elif object.punk_entity_type == "SOUND_3D":
#        export_sound_3d(f, object)
#    elif object.punk_entity_type == "RIGID":
#        export_rigid_body(f, object)
#    elif object.punk_entity_type == "CHARACTER":
#        export_character(f, object)
#    elif object.punk_entity_type == "CAMERA":
#        if type(object.data) == bpy.types.Camera:
#            export_camera_node(f, object)
#    elif object.punk_entity_type == "COLLISION_MESH":
#        export_collision_mesh(f, object)
#    return
