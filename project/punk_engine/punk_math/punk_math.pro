######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_math

INCLUDEPATH += ../../../source

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_system

SOURCES += \    
    ../../../source/math/mat4.cpp \
    ../../../source/math/mat3.cpp \
    ../../../source/math/quat.cpp \
    ../../../source/math/math_error.cpp \
    ../../../source/math/matrix_helper.cpp \
    ../../../source/math/bounding_sphere.cpp \
    ../../../source/math/line2d.cpp \
    ../../../source/math/volume_construction.cpp \
    ../../../source/math/root_find.cpp \
    ../../../source/math/absolute_value.cpp \
    ../../../source/math/square_root.cpp \
    ../../../source/math/power.cpp \
    ../../../source/math/trigonometry.cpp \
    ../../../source/math/sphere.cpp \
    ../../../source/math/relations.cpp \
    ../../../source/math/triangle2d.cpp \
    ../../../source/math/triangle3d.cpp \
    ../../../source/math/array.cpp \
    ../../../source/math/polygon3d.cpp \
    ../../../source/math/ellipsoid.cpp \
    ../../../source/math/portal.cpp \
    ../../../source/math/clip_space.cpp \
    ../../../source/math/convex_shape_mesh.cpp \
    ../../../source/math/frustum_plane.cpp \    
    ../../../source/math/perspective_decoder.cpp \
    ../../../source/math/min_max.cpp \
    ../../../source/math/metric/value.cpp \
    ../../../source/math/helper.cpp \
    ../../../source/math/rect.cpp \        
    ../../../source/math/weighted_point.cpp \
    ../../../source/math/astar.cpp \
    ../../../source/math/frustum_core.cpp \
    ../../../source/math/graham.cpp \
    ../../../source/math/gramm_shmidt.cpp \
    ../../../source/math/icurve.cpp \
    ../../../source/math/ifrustum.cpp \
    ../../../source/math/linear_equation_solver.cpp \
    ../../../source/math/math.cpp \
    ../../../source/math/noise.cpp \
    ../../../source/math/noiseutils.cpp \
    ../../../source/math/random.cpp \
    ../../../source/math/recount.cpp \
    ../../../source/math/spherical.cpp \
    ../../../source/math/tuple.cpp


HEADERS += \
    ../../../source/math/vec4.h \
    ../../../source/math/vec3.h \
    ../../../source/math/vec2.h \
    ../../../source/math/mat4.h \
    ../../../source/math/mat3.h \
    ../../../source/math/mat2.h \
    ../../../source/math/quat.h \
    ../../../source/math/math_error.h \
    ../../../source/math/matrix_helper.h \
    ../../../source/math/bounding_box.h \
    ../../../source/math/bounding_sphere.h \
    ../../../source/math/plane.h \
    ../../../source/math/line3d.h \
    ../../../source/math/line2d.h \
    ../../../source/math/volume_construction.h \
    ../../../source/math/root_find.h \
    ../../../source/math/absolute_value.h \
    ../../../source/math/square_root.h \
    ../../../source/math/power.h \
    ../../../source/math/trigonometry.h \
    ../../../source/math/sphere.h \
    ../../../source/math/relations.h \
    ../../../source/math/aabb.h \
    ../../../source/math/triangle3d.h \
    ../../../source/math/triangle2d.h \
    ../../../source/math/array.h \
    ../../../source/math/polygon3d.h \
    ../../../source/math/ellipsoid.h \
    ../../../source/math/portal.h \
    ../../../source/math/clip_space.h \
    ../../../source/math/convex_shape_mesh.h \
    ../../../source/math/frustum_plane.h \
    ../../../source/math/frustum_points.h \
    ../../../source/math/frustum.h \
    ../../../source/math/perspective_decoder.h \
    ../../../source/math/min_max.h \
    ../../../source/math/metric/value.h \
    ../../../source/math/helper.h \
    ../../../source/math/rect.h \
    ../../../source/math/curve.h \
    ../../../source/math/spline.h \
    ../../../source/math/weighted_point.h \
    ../../../source/math/astar.h \
    ../../../source/math/catmull_rom_spline.h \
    ../../../source/math/complex.h \
    ../../../source/math/constants.h \
    ../../../source/math/frustum_core.h \
    ../../../source/math/graham.h \
    ../../../source/math/gramm_shmidt.h \
    ../../../source/math/header_matrix.h \
    ../../../source/math/icurve.h \
    ../../../source/math/ifrustum.h \
    ../../../source/math/interpolation.h \
    ../../../source/math/ispline.h \
    ../../../source/math/linear_equation_solver.h \
    ../../../source/math/low_level_math.h \
    ../../../source/math/math.h \
    ../../../source/math/matrix.h \
    ../../../source/math/module.h \
    ../../../source/math/noise.h \
    ../../../source/math/noiseutils.h \
    ../../../source/math/nrm.h \
    ../../../source/math/polygon.h \
    ../../../source/math/random.h \
    ../../../source/math/ray.h \
    ../../../source/math/recount.h \
    ../../../source/math/region.h \
    ../../../source/math/smart_matrix.h \
    ../../../source/math/spherical.h \
    ../../../source/math/tuple.h \
    ../../../source/math/type.h \
    ../../../source/math/line.h \
    ../../../source/math/calculate_native_axis.h \
    ../../../source/math/create_covariance_matrix.h \
    ../../../source/math/calculate_average.h \
    ../../../source/math/triangle.h
