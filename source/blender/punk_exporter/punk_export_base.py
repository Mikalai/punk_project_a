import bpy
import copy
from copy import deepcopy

text_offset = 0 #used to print data nice
path = ""
used_entities = {}
vertex_groups = {}

def push_entity(type, object):
    if not(type in used_entities.keys()):
        used_entities[type] = set()
    print("Add " + type + " " + object.name)
    used_entities[type].add(object)
    return


#   export single float
def export_float(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0}\n".format(value))
    end_block(f)
    return

#   export single vec4
def export_vec4(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0} {1} {2} {3}\n".format(value[0], value[1], value[2], value[3]))
    end_block(f)
    return

#   export single vec4
def export_vec3(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0} {1} {2}\n".format(value[0], value[1], value[2]))
    end_block(f)
    return

def export_quat(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0} {1} {2} {3}\n".format(value[0], value[1], value[2], value[3]))
    end_block(f)
    return

#   export single string
def export_string(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%s\n" % value)
    end_block(f)
    return

def export_mat4(f, name, matrix):
    start_block(f, name)
    for v in matrix:  
        make_offset(f)      
        f.write("{0} {1} {2} {3}\n".format(v[0], v[1], v[2], v[3]))
    end_block(f)
    return

def inc_offset():
    global text_offset
    text_offset = text_offset + 1
    return

def dec_offset():
    global text_offset
    text_offset = text_offset - 1
    return

def make_offset(f):
    for i in range(text_offset):
        f.write("  ")
    return

def start_block(f, title):
    make_offset(f)
    f.write("%s\n" % title)
    make_offset(f)
    f.write("{\n")
    inc_offset()
    return

def end_block(f):
    dec_offset()
    make_offset(f)
    f.write("}\n\n")
    return

def export_name(f, object):
    start_block(f, "*name")
    
    make_offset(f)
    f.write("%s\n" % object.name)
    
    end_block(f)
    return
