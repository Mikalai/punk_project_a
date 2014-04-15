include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_blender

INCLUDEPATH += ../../../source

OTHER_FILES += \
    ../../../source/blender/punk_exporter/__init__.py \
    ../../../source/blender/punk_exporter/punk_export.py \
    ../../../source/blender/punk_exporter/punk_export_action.py \
    ../../../source/blender/punk_exporter/punk_export_armature.py \
    ../../../source/blender/punk_exporter/punk_export_base.py \
    ../../../source/blender/punk_exporter/punk_export_bones_weights 1.py \
    ../../../source/blender/punk_exporter/punk_export_bones_weights.py \
    ../../../source/blender/punk_exporter/punk_export_bounding_box.py \
    ../../../source/blender/punk_exporter/punk_export_camera.py \
    ../../../source/blender/punk_exporter/punk_export_face_normals.py \
    ../../../source/blender/punk_exporter/punk_export_faces.py \
    ../../../source/blender/punk_exporter/punk_export_light.py \
    ../../../source/blender/punk_exporter/punk_export_material.py \
    ../../../source/blender/punk_exporter/punk_export_model.py \
    ../../../source/blender/punk_exporter/punk_export_navi_mesh.py \
    ../../../source/blender/punk_exporter/punk_export_normals.py \
    ../../../source/blender/punk_exporter/punk_export_path.py \
    ../../../source/blender/punk_exporter/punk_export_river.py \
    ../../../source/blender/punk_exporter/punk_export_skin_mesh.py \
    ../../../source/blender/punk_exporter/punk_export_static_mesh.py \
    ../../../source/blender/punk_exporter/punk_export_sun.py \
    ../../../source/blender/punk_exporter/punk_export_terrain.py \
    ../../../source/blender/punk_exporter/punk_export_texture_coords.py \
    ../../../source/blender/punk_exporter/punk_export_texture_slots.py \
    ../../../source/blender/punk_exporter/punk_export_vertex_position.py \
    ../../../source/blender/punk_exporter/punk_exporter_2_60.py \
    ../../../source/blender/punk_exporter/punk_export_static_mesh_node.py \
    ../../../source/blender/punk_exporter/punk_export_object.py \
    ../../../source/blender/punk_exporter/punk_export_skin_mesh_node.py \
    ../../../source/blender/punk_exporter/punk_export_transform.py

