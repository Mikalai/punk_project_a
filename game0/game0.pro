#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T23:42:27
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game0
TEMPLATE = app

DEFINES += USE_QT USE_NOISE PUNK_STATIC_LIB WIN32

INCLUDEPATH += ..\source \
    ..\source\math\libnoise\noise\src \
    ..\source\math\libnoise\noiseutils


SOURCES += main.cpp\
        main_window.cpp \
    editstring.cpp \
    db.cpp \
    editnames.cpp \
    canvas.cpp \
    manage_building_schema.cpp \
    building_schema.cpp \
    polygon.cpp \
    point.cpp \
    ui_text.cpp \
    wall_material.cpp \
    material.cpp \
    roof_material.cpp \
    edit_materials.cpp \
    floor_design.cpp \
    floor_schema.cpp \
    wall_schema.cpp \
    ../source/math/array.cpp \
    ../source/math/astar.cpp \
    ../source/math/frustum_plane.cpp \
    ../source/math/graham.cpp \
    ../source/math/helper.cpp \
    ../source/math/random.cpp \
    ../source/math/recount.cpp \
    ../source/math/relations.cpp \
    ../source/math/root_find.cpp \
    ../source/math/spherical.cpp \
    ../source/math/trigonometry.cpp \
    ../source/math/libnoise/noiseutils/noiseutils.cpp \
    ../source/math/libnoise/noise/src/latlon.cpp \
    ../source/math/libnoise/noise/src/noisegen.cpp \
    ../source/math/libnoise/noise/src/module/abs.cpp \
    ../source/math/libnoise/noise/src/module/add.cpp \
    ../source/math/libnoise/noise/src/module/billow.cpp \
    ../source/math/libnoise/noise/src/module/blend.cpp \
    ../source/math/libnoise/noise/src/module/cache.cpp \
    ../source/math/libnoise/noise/src/module/checkerboard.cpp \
    ../source/math/libnoise/noise/src/module/clamp.cpp \
    ../source/math/libnoise/noise/src/module/const.cpp \
    ../source/math/libnoise/noise/src/module/curve.cpp \
    ../source/math/libnoise/noise/src/module/cylinders.cpp \
    ../source/math/libnoise/noise/src/module/displace.cpp \
    ../source/math/libnoise/noise/src/module/exponent.cpp \
    ../source/math/libnoise/noise/src/module/invert.cpp \
    ../source/math/libnoise/noise/src/module/max.cpp \
    ../source/math/libnoise/noise/src/module/min.cpp \
    ../source/math/libnoise/noise/src/module/modulebase.cpp \
    ../source/math/libnoise/noise/src/module/multiply.cpp \
    ../source/math/libnoise/noise/src/module/perlin.cpp \
    ../source/math/libnoise/noise/src/module/power.cpp \
    ../source/math/libnoise/noise/src/module/ridgedmulti.cpp \
    ../source/math/libnoise/noise/src/module/rotatepoint.cpp \
    ../source/math/libnoise/noise/src/module/scalebias.cpp \
    ../source/math/libnoise/noise/src/module/scalepoint.cpp \
    ../source/math/libnoise/noise/src/module/select.cpp \
    ../source/math/libnoise/noise/src/module/spheres.cpp \
    ../source/math/libnoise/noise/src/module/terrace.cpp \
    ../source/math/libnoise/noise/src/module/translatepoint.cpp \
    ../source/math/libnoise/noise/src/module/turbulence.cpp \
    ../source/math/libnoise/noise/src/module/voronoi.cpp \
    ../source/math/libnoise/noise/src/model/cylinder.cpp \
    ../source/math/libnoise/noise/src/model/line.cpp \
    ../source/math/libnoise/noise/src/model/plane.cpp \
    ../source/math/libnoise/noise/src/model/sphere.cpp \
    bounding_volume.cpp \
    window_type.cpp \
    window_schema.cpp \
    object_type.cpp \
    door_type.cpp \
    door_schema.cpp \
    stair_schema.cpp \
    stairs_type.cpp \
    vizualization_viewport.cpp \
    world.cpp \
    ../source/string/buffer.cpp \
    ../source/string/buffer_error.cpp \
    ../source/string/string.cpp \
    ../source/string/string_error.cpp \
    ../source/string/string_list.cpp \
    ../source/interfaces/character.cpp \
    ../source/core/guid.cpp \
    charactermanager.cpp \
    locationwidget.cpp


HEADERS  += main_window.h \
    editstring.h \
    db.h \
    string_delegate.h \
    editnames.h \
    canvas.h \
    manage_building_schema.h \
    building_schema.h \
    polygon.h \
    point.h \
    ui_text.h \
    wall_material.h \
    material.h \
    roof_material.h \
    edit_materials.h \
    floor_design.h \
    floor_schema.h \
    wall_schema.h \
    ../source/math/aabb.h \
    ../source/math/absolute_value.h \
    ../source/math/array.h \
    ../source/math/astar.h \
    ../source/math/bounding_box.h \
    ../source/math/bounding_sphere.h \
    ../source/math/calculate_average.h \
    ../source/math/calculate_native_axis.h \
    ../source/math/catmull_rom_spline.h \
    ../source/math/clip_segment.h \
    ../source/math/clip_space.h \
    ../source/math/complex.h \
    ../source/math/constants.h \
    ../source/math/convex_shape_mesh.h \
    ../source/math/create_covariance_matrix.h \
    ../source/math/ellipsoid.h \
    ../source/math/forward.h \
    ../source/math/frustum_core.h \
    ../source/math/frustum_plane.h \
    ../source/math/frustum_points.h \
    ../source/math/graham.h \
    ../source/math/gramm_shmidt.h \
    ../source/math/header_matrix.h \
    ../source/math/helper.h \
    ../source/math/line.h \
    ../source/math/line2d.h \
    ../source/math/line3d.h \
    ../source/math/linear_equation_solver.h \
    ../source/math/low_level_math.h \
    ../source/math/mat2.h \
    ../source/math/mat3.h \
    ../source/math/mat4.h \
    ../source/math/math.h \
    ../source/math/math_error.h \
    ../source/math/matrix.h \
    ../source/math/matrix_helper.h \
    ../source/math/min_max.h \
    ../source/math/module.h \
    ../source/math/nrm.h \
    ../source/math/pe_power.h \
    ../source/math/perspective_decoder.h \
    ../source/math/plane.h \
    ../source/math/polygon.h \
    ../source/math/polygon3d.h \
    ../source/math/portal.h \
    ../source/math/quat.h \
    ../source/math/random.h \
    ../source/math/ray.h \
    ../source/math/recount.h \
    ../source/math/rect.h \
    ../source/math/region.h \
    ../source/math/relations.h \
    ../source/math/root_find.h \
    ../source/math/smart_matrix.h \
    ../source/math/sphere.h \
    ../source/math/spherical.h \
    ../source/math/square_root.h \
    ../source/math/symmetric_eigen_system.h \
    ../source/math/tbn_space.h \
    ../source/math/triangle.h \
    ../source/math/triangle2d.h \
    ../source/math/triangle3d.h \
    ../source/math/trigonometry.h \
    ../source/math/tuple.h \
    ../source/math/type.h \
    ../source/math/vec2.h \
    ../source/math/vec3.h \
    ../source/math/vec4.h \
    ../source/math/volume_construction.h \
    ../source/math/weighted_point.h \
    ../source/math/libnoise/noiseutils/noiseutils.h \
    ../source/math/libnoise/noise/src/basictypes.h \
    ../source/math/libnoise/noise/src/exception.h \
    ../source/math/libnoise/noise/src/interp.h \
    ../source/math/libnoise/noise/src/latlon.h \
    ../source/math/libnoise/noise/src/mathconsts.h \
    ../source/math/libnoise/noise/src/misc.h \
    ../source/math/libnoise/noise/src/noise.h \
    ../source/math/libnoise/noise/src/noisegen.h \
    ../source/math/libnoise/noise/src/vectortable.h \
    ../source/math/libnoise/noise/src/module/abs.h \
    ../source/math/libnoise/noise/src/module/add.h \
    ../source/math/libnoise/noise/src/module/billow.h \
    ../source/math/libnoise/noise/src/module/blend.h \
    ../source/math/libnoise/noise/src/module/cache.h \
    ../source/math/libnoise/noise/src/module/checkerboard.h \
    ../source/math/libnoise/noise/src/module/clamp.h \
    ../source/math/libnoise/noise/src/module/const.h \
    ../source/math/libnoise/noise/src/module/curve.h \
    ../source/math/libnoise/noise/src/module/cylinders.h \
    ../source/math/libnoise/noise/src/module/displace.h \
    ../source/math/libnoise/noise/src/module/exponent.h \
    ../source/math/libnoise/noise/src/module/invert.h \
    ../source/math/libnoise/noise/src/module/max.h \
    ../source/math/libnoise/noise/src/module/min.h \
    ../source/math/libnoise/noise/src/module/module.h \
    ../source/math/libnoise/noise/src/module/modulebase.h \
    ../source/math/libnoise/noise/src/module/multiply.h \
    ../source/math/libnoise/noise/src/module/perlin.h \
    ../source/math/libnoise/noise/src/module/power.h \
    ../source/math/libnoise/noise/src/module/ridgedmulti.h \
    ../source/math/libnoise/noise/src/module/rotatepoint.h \
    ../source/math/libnoise/noise/src/module/scalebias.h \
    ../source/math/libnoise/noise/src/module/scalepoint.h \
    ../source/math/libnoise/noise/src/module/select.h \
    ../source/math/libnoise/noise/src/module/spheres.h \
    ../source/math/libnoise/noise/src/module/terrace.h \
    ../source/math/libnoise/noise/src/module/translatepoint.h \
    ../source/math/libnoise/noise/src/module/turbulence.h \
    ../source/math/libnoise/noise/src/module/voronoi.h \
    ../source/math/libnoise/noise/src/model/cylinder.h \
    ../source/math/libnoise/noise/src/model/line.h \
    ../source/math/libnoise/noise/src/model/model.h \
    ../source/math/libnoise/noise/src/model/plane.h \
    ../source/math/libnoise/noise/src/model/sphere.h \
    bounding_volume.h \
    window_type.h \
    window_schema.h \
    object_type.h \
    door_type.h \
    door_schema.h \
    stair_schema.h \
    stairs_type.h \
    vizualization_viewport.h \
    world.h \
    ../source/interfaces/location.h \
    ../source/interfaces/transform2d.h \
    ../source/interfaces/character.h \
    ../source/interfaces/body.h \
    ../source/interfaces/body_action.h \
    ../source/interfaces/knowledge.h \
    ../source/string/buffer.h \
    ../source/string/buffer_error.h \
    ../source/string/module.h \
    ../source/string/string.h \
    ../source/string/string_error.h \
    ../source/string/string_list.h \
    ../source/interfaces/time_dependent.h \
    ../source/interfaces/body_power.h \
    ../source/interfaces/body_temperature.h \
    ../source/interfaces/environment.h \
    ../source/core/guid.h \
    charactermanager.h \
    locationwidget.h

FORMS    += main_window.ui \
    editstring.ui \
    editnames.ui \
    manage_building_schema.ui \
    edit_materials.ui \
    charactermanager.ui \
    locationwidget.ui
