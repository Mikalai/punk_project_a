from . import punk_export_base
from .punk_export_base import *

import bpy
import copy
from copy import deepcopy

#
#   export all animation
#    
def export_actions(f):       
    for action in bpy.data.actions:
        if (action != None):
            export_action(f, action)
    return

#
#   export one action
#
def export_action(f, action):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = action.name + ".action"
    
    f = open(file, "w")

    f.write("ACTIONTEXT\n")
            
    start_block(f, action.name)
    
    try:
        start = int(action.frame_range[0])
        end = int(action.frame_range[1])
        #start_block(f, "*timing")
        #make_offset(f)
        #f.write("%d %d\n" % (start, end))
        #end_block(f)    #*timing
    except:
        print("erorr in timings")            
    
    tracks = dict()        
    
    #   cook tracks from curves
    #   keyframe points in each channel should be equal
    for curve in action.fcurves:         
        index = curve.array_index
        track_name = curve.group.name                    
        #   get all location tracks collection
        object_tracks = tracks.get(track_name)
        if object_tracks == None:
            object_tracks = dict()
            tracks[track_name] = object_tracks
        
        #   determine whether it is location or rotation.
        #   rotation should be represented only as quaternion
        if curve.data_path.rfind("location") != -1:
            track = object_tracks.get(curve.data_path)
            #   if no, than create new location tracks collection
            if track == None:
                track = list()
                object_tracks[curve.data_path] = track 
            #   [time, [x, y, z]]
            etalon = [0, [0.0, 0.0, 0.0]]
        if curve.data_path.rfind("scale") != -1:
            track = object_tracks.get(curve.data_path)
            #   if no, than create new location tracks collection
            if track == None:
                track = list()
                object_tracks[curve.data_path] = track 
            #   [time, [x, y, z]]
            etalon = [0, [0.0, 0.0, 0.0]]
        if curve.data_path.rfind("rotation_quaternion") != -1:
            track = object_tracks.get(curve.data_path)
            if track == None:
                track = list()
                object_tracks[curve.data_path] = track
            #   [time, [w, x, y, z]]
            etalon = [0, [0.0, 0.0, 0.0, 0.0]]
        #   extract points from curve
        for key_index in range(0, len(curve.keyframe_points)):
            #   define location to write data
            #   if point already in track we use it
            #   otherwise create new point and add it
            #   to the track
            if len(track) > key_index:
                point = track[key_index]
            else:
                point = deepcopy(etalon)
                track.append(point)     
            #   retrieve cure           
            key = curve.keyframe_points[key_index]
            point[0] = int(key.co[0])
            point[1][index] = key.co[1]
      
    #   export all tracks 
    for object_name in tracks:
        object_tracks = tracks[object_name]
        #   write bone name that is affected by this curve
        #if list(object_tracks.keys())[0].rfind("bones") != -1:
        #    start_block(f, "*track")
        #    export_string(f, "*name", object_name)
        ##   otherwise just mark this track as suitable for any object
        #else:
       # start_block(f, "*animation")
            
        #   export all tracks for current object    
        for track_name in object_tracks:
            track = object_tracks[track_name]            
            #   export position
            if track_name.rfind("location") != -1:
                start_block(f, "*track_vec3")
                export_string(f, "*name", object_name + ":Location" )
                start_block(f, "*keys")
                for point in track:
                    make_offset(f)
                    f.write("%5d %16f %16f %16f\n" % (point[0], point[1][0], point[1][1], point[1][2]))
                end_block(f)
                end_block(f) #  *track
            if track_name.rfind("scale") != -1:
                start_block(f, "*track_vec3")
                export_string(f, "*name", object_name + ":Scale")
                start_block(f, "*keys")
                for point in track:
                    make_offset(f)
                    f.write("%5d %16f %16f %16f\n" % (point[0], point[1][0], point[1][1], point[1][2]))
                end_block(f);
                end_block(f) #  *track
            #   epxort rotation
            if track_name.find("rotation_quaternion") != -1:
                start_block(f, "*track_quat")
                export_string(f, "*name", object_name + ":Rotation")
                start_block(f, "*keys")
                for point in track:
                    make_offset(f)
                    f.write("%5d %16f %16f %16f %16f\n" % (point[0], point[1][0], point[1][1], point[1][2], point[1][3]))
                end_block(f)
                end_block(f) #  *rotation_track
        
       # end_block(f)    # *bone_animation or *object_animation
    end_block(f)    # *action   
    
    text_offset = old
    return

punk_register_export_func("ACTIONS", export_actions)
