from . import punk_export_base
from .punk_export_base import *
import bpy

def export_light_node(f, object):
    print("Export light node")
    export_object = punk_get_export_func("OBJECT")
    export_location = punk_get_export_func("OBJECT.LOCATION")
    if export_object == None or export_location == None:
        return

    if object.data == None:
        return
    light = object.data    

    start_block(f, "*node")
    export_string(f, "*name", "Transform")    
    export_string(f, "*entity_name", object.name + ".transform")
    push_entity("*transform", object)

    start_block(f, "*node")
    try:
        if type(light) == bpy.types.PointLamp:
            print("PointLamp")
            export_string(f, "*name", "PointLight")
            export_string(f, "*entity_name", object.name + ".point_lamp")
            push_entity("*point_lamp", object)
        elif type(light) == bpy.types.SunLamp:
            print("DirectionalLamp")
            export_string(f, "*name", "DirectionalLight")
            export_string(f, "*entity_name", object.name + ".directional_lamp")
            push_entity("*directional_lamp", object)
        else:
            raise Exception("Unsupported light type")
    except BaseException as err:
        print("Something went wrong {0}".format(err))
    except:
        print("Something went wrong")
    
    
    for child in object.children:
        export_object(f, child)
    
    end_block(f)    # light
    end_block(f) #  Transform    

    return

punk_register_export_func("LIGHT", export_light_node)
