#ifndef _H_PUNK_VIRTUAL_KEY_WORDS
#define _H_PUNK_VIRTUAL_KEY_WORDS

#include <config.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace IoModule
{	
	enum KeywordCode
	{		
		WORD_BAD_KEYWORD,					// 0
		WORD_ANY,
		WORD_OPEN_BRACKET,					// 1
		WORD_CLOSE_BRACKET,					// 2
		WORD_VEC3F,
		WROD_VEC4F, 
		WORD_VEC3FV,
		WORD_VEC3IV,
		WORD_QUAT,
		WORD_UINT32,
		WORD_FLOAT,
		WORD_MATRIX4X4F,
		WORD_FACTOR,
		WORD_STRING,
		WORD_VEC3VEC2VF,
		WORD_OBJECT,						// 3
		WORD_BOUNDING_BOX,					// 4
		WORD_LOCATION,						// 5
		WORD_WORLD_MATRIX,					// 7
		WORD_LOCAL_MATRIX,					// 8
		WORD_STATIC_MESH,					// 9
		WORD_STATIC_MESHES,					// 9
		WORD_STATIC_MESH_NODE,
		WORD_BONE_MATRIX,
		WORD_SKIN_MESH,
		WORD_SKIN_MESHES,
		WORD_SKIN_MESH_NODE,
		WORD_VERTEX_POSITION,				// 10
		WORD_NORMALS,						// 11
		WORD_FACES,							// 12
		WORD_VERTEX_POSITIONS_ID,			// 13
		WORD_ARMATURE,						// 15
		WORD_ARMATURE_NODE,
		WORD_BONE,							// 16
		WORD_NAME,							// 17
		WORD_ACTIONS,						// 18
		WORD_POS_X,							// 19
		WORD_POS_Y,					// 6
		WORD_POS_Z,					// 6
		WORD_ROT_W,					// 6
		WORD_ROT_X,					// 6
		WORD_ROT_Y,					// 6
		WORD_ROT_Z,					// 6
		WORD_PARENT,					// 6
		WORD_TEXTURE_COORD,					// 6
		WORD_MATERIAL,					// 6
		WORD_NORMAL_MAP,					// 6
		WORD_DIFFUSE_MAP,					// 6
		WORD_SPECULAR_MAP,					// 6
		WORD_MATERIALS,					// 6
		WORD_GIMBAL_TRANSFORM,					// 6
		WORD_ACTION,					// 6
		WORD_ARMATURES,					// 6
		WORD_FRAMES,					// 6
		WORD_TEXTURE,					// 6
		WORD_TIMING,					// 6
		WORD_PARENT_INVERSED_MATRIX,					// 6
		WORD_LENGTH,					// 6
		WORD_ALPHA,									//{ , "*alpha" },
		WORD_AMBIENT,								//{ , "*ambient" },
		WORD_DARKNESS,								//{ , "*darkness" },
		WORD_DIFFUSE_COLOR,							//{ , "*diffuse_color" },
		WORD_DIFFUSE_FRESNEL,						//{ , "*diffuse_fresne" },
		WORD_DIFFUSE_FRESNEL_FACTOR,				//{ , "*diffuse_fresnel_factor" },
		WORD_DIFFUSE_INTENSITY,						//{ , "*diffuse_intensity" },
		WORD_EMIT,									//{ , "*emit" },
		WORD_MIRROR_COLOR,							//{ , "*mirror_color" },
		WORD_ROUGHNESS,								//{ , "*roughness" },
		WORD_SPECULAR_ALPHA,						//{ , "*specular_alpha" },
		WORD_SPECULAR_COLOR,						//{ , "*specular_color" },
		WORD_SPECULAR_HARDNESS,						//{ , "*specular_hardness" },
		WORD_SPECULAR_INTENSITY,					//{ , "*specular_intensity" },
		WORD_SPECULAR_IOR,							//{ , "*specular_ior" },
		WORD_SPECULAR_SLOPE,						//{ , "*specular_slope" },
		WORD_TRANSLUCENCY,							//{ , "*translucency" },
		WORD_SOUND,					// 6
		WORD_FILENAME,					// 6
		WORD_VOLUME,					// 6
		WORD_PITCH,					// 6
		WORD_MAX_DISTANCE,					// 6
		WORD_TRANSFORM,
		WORD_REFERENCE_DISTANCE,					// 6
		WORD_CONE_ANGLE_INNER,					// 6
		WORD_CONE_ANGLE_OUTER,					// 6
		WORD_CONE_VOLUME_OUTER,					// 6
		WORD_ATTENUATION,					// 6
		WORD_TYPE,					// 6
		WORD_POINT_LIGHT,					// 6
		WORD_LIGHT_TYPE,					// 6
		WORD_COLOR,					// 6
		WORD_DISTANCE,					// 6
		WORD_ENERGY,					// 6
		WORD_FALLOFF_TYPE,					// 6
		WORD_LINEAR_ATTENUATION,					// 6
		WORD_QUADRATIC_ATTENUATION,					// 6
		WORD_REFERENCE, 					// 6
		WORD_MATERIAL_REF,					// 6
		WORD_ACTIONS_REF,					// 6
		WORD_ACTION_REF,					// 6
		WORD_CAMERA,					// 6
		WORD_FOV,					// 6
		WORD_NEAR_PLANE,					// 6
		WORD_FAR_PLANE,					// 6
		WORD_FOCUS,					// 6
		WORD_ORTHO_SCALE,					// 6
		WORD_COLLISION_MESH,					// 6
		WORD_LOCATION_INDOOR,					// 6
		WORD_CONVEX_MESH,					// 6
		WORD_MATERIAL_NODE,					// 6
		WORD_BONE_NODE,
		WORD_TRANSFORM_NODE,					// 6
		WORD_PORTAL,					// 6
		WORD_PORTAL_NODE,					// 6
		WORD_FACE_NORMALS,
		WORD_MAPDESCTEXT,
		WORD_REF,
		WORD_RAW_DATA_SOURCE,
		WORD_NUM_BLOCKS,
		WORD_BLOCK_SCALE,
		WORD_BLOCK_SIZE,
		WORD_HEIGHT_SCALE,
		WORD_WORLD_ORIGIN,
		WORD_CELL,		
		WORD_ARMATURETEXT,
		WORD_ACTIONTEXT,
		WORD_STATICMESHTEXT,
        WORD_MATERIALTEXT,
        WORD_NAVIMESHTEXT,
		WORD_NAVI_MESH,
        WORD_PATHTEXT,
        WORD_POINT,
		WORD_WEIGHTED_POINT,
        WORD_SPLINE,
        WORD_POSITION,
        WORD_WEIGHT,
        WORD_SCALE,
        WORD_IMAGE,
        WORD_SUN,
        WORD_SUN_NODE,
        WORD_SPECULAR_INTENSITY_MAP,		
        WORD_RIVERTEXT,
        WORD_SCENETEXT,
		WORD_SCENE_GRAPH,
        WORD_SUNTEXT,
        WORD_NAVIMESH_NODE,
        WORD_PATH_NODE,
        WORD_TERRAIN_NODE,
        WORD_RIVER_NODE,
        WORD_MESH,
        WORD_TERRAINTEXT,
        WORD_FLOW_SPEED,
        WORD_FLOW_DIRECTION,
        WORD_SKINMESH_TEXT,
        WORD_NODE,
        WORD_ROTATION,
        WORD_ENTITY_NAME,
        WORD_DIRECTION,
        WORD_DIRLIGHTTEXT,
		WORD_SPOTLIGHTTEXT,
		WORD_POINTLIGHTTEXT,
		WORD_TRANSFORMTEXT,
		WORD_ARMATURE_SCHEMA_TEXT,
		WORD_ARMATURE_SCHEMA,
		WORD_VERTEX_BONES_WEIGHTS,
		WORD_VERTEX_INDEX,
		WORD_BONES_WEIGHTS,
		WORD_WEIGHTS,
		WORD_DIFFUSE_TEXTURE_SLOT,
		WORD_NORMAL_TEXTURE_SLOT,
		WORD_SPECULAR_TEXTURE_SLOT,
		WORD_DIRECTIONAL_LIGHT,
		WORD_SPOT_LIGHT,
		WORD_CURVE_PATH,
		WORD_CAMERATEXT,
		WORD_PERSPECTIVE_CAMERA,
		WORD_ORTHO_CAMERA,
		WORD_PANORAMIC_CAMERA,
		WORD_UP_VECTOR,
		WORD_TRACK_VEC3,
		WORD_TRACK_VEC4,
		WORD_TRACK_FLOAT,
		WORD_TRACK_QUAT,
		WORD_TRACK_MAT4,
		WORD_KEYS,
		WORD_INDEX,
		WORD_ARMATURE_MATRIX
	};

	struct Record
	{
		KeywordCode code;
        const char* word;
	};

	static const Record Keyword[] = {
			{ WORD_BAD_KEYWORD, "" },
			{ WORD_OPEN_BRACKET, "{" },
			{ WORD_CLOSE_BRACKET, "}" },
			{ WORD_OBJECT, "*object" },
			{ WORD_BOUNDING_BOX, "*bounding_box" },
			{ WORD_LOCATION, "*location" },
			{ WORD_WORLD_MATRIX, "*world_matrix" },
			{ WORD_LOCAL_MATRIX, "*local_matrix" },
			{ WORD_BONE_MATRIX, "*bone_matrix" },
			{ WORD_STATIC_MESH, "*static_mesh" },
			{ WORD_STATIC_MESHES, "*static_meshes" },
			{ WORD_STATIC_MESH_NODE, "*static_mesh_node" },
			{ WORD_SKIN_MESH, "*skin_mesh" },
			{ WORD_SKIN_MESHES, "*skin_meshes" },
			{ WORD_SKIN_MESH_NODE, "*skin_mesh_node" },
			{ WORD_VERTEX_POSITION, "*vertex_position" },
			{ WORD_NORMALS, "*normals" },
			{ WORD_FACES, "*faces" },
			{ WORD_VERTEX_POSITIONS_ID, "*vertex_positions_id" },
			{ WORD_ARMATURE_NODE, "*armature_node" },
			{ WORD_ARMATURE, "*armature" },
			{ WORD_BONE, "*bone" },
			{ WORD_NAME, "*name" },
			{ WORD_ACTIONS, "*actions" },
			{ WORD_POS_X, "*pos_x" },
			{ WORD_POS_Y, "*pos_y" },
			{ WORD_POS_Z, "*pos_z" },
			{ WORD_ROT_W, "*rot_w" },
			{ WORD_ROT_X, "*rot_x" },
			{ WORD_ROT_Y, "*rot_y" },
			{ WORD_ROT_Z, "*rot_z" },
			{ WORD_PARENT, "*parent" },
			{ WORD_TEXTURE_COORD, "*tex_coord" },
			{ WORD_MATERIAL, "*material" },
			{ WORD_NORMAL_MAP, "*normal_map" },
			{ WORD_DIFFUSE_MAP, "*diffuse_map" },
			{ WORD_SPECULAR_MAP, "*specular_map" },
			{ WORD_MATERIALS, "*materials" },
			{ WORD_GIMBAL_TRANSFORM, "*gimbal_transform" },
			{ WORD_ACTION, "*action" },
			{ WORD_ARMATURES, "*armatures" },
			{ WORD_FRAMES, "*frames" },
			{ WORD_TEXTURE, "*texture" },
			{ WORD_TIMING, "*timing" },
			{ WORD_PARENT_INVERSED_MATRIX, "*parent_inverse_matrix" },
			{ WORD_LENGTH, "*length" },
			{ WORD_ALPHA, "*alpha" },
			{ WORD_AMBIENT, "*ambient" },
			{ WORD_DARKNESS, "*darkness" },
			{ WORD_DIFFUSE_COLOR, "*diffuse_color" },
			{ WORD_DIFFUSE_FRESNEL, "*diffuse_fresnel" },
			{ WORD_DIFFUSE_FRESNEL_FACTOR, "*diffuse_fresnel_factor" },
			{ WORD_DIFFUSE_INTENSITY, "*diffuse_intensity" },
			{ WORD_EMIT, "*emit" },
			{ WORD_MIRROR_COLOR, "*mirror_color" },
			{ WORD_ROUGHNESS, "*roughness" },
			{ WORD_SPECULAR_ALPHA, "*specular_alpha" },
			{ WORD_SPECULAR_COLOR, "*specular_color" },
			{ WORD_SPECULAR_HARDNESS, "*specular_hardness" },
			{ WORD_SPECULAR_INTENSITY, "*specular_intensity" },
			{ WORD_SPECULAR_IOR, "*specular_ior" },
			{ WORD_SPECULAR_SLOPE, "*specular_slope" },
			{ WORD_TRANSLUCENCY, "*translucency" },
			{ WORD_SOUND, "*sound" },
			{ WORD_FILENAME, "*filename" },
			{ WORD_VOLUME, "*volume" },
			{ WORD_PITCH, "*pitch" },
			{ WORD_MAX_DISTANCE, "*max_distance" },
			{ WORD_REFERENCE_DISTANCE, "*reference_distance" },
			{ WORD_CONE_ANGLE_INNER, "*cone_angle_inner" },
			{ WORD_CONE_ANGLE_OUTER, "*cone_angle_outer" },
			{ WORD_CONE_VOLUME_OUTER, "*cone_volume_outer" },
			{ WORD_ATTENUATION, "*attenuation" },
			{ WORD_TYPE, "*type" },
			{ WORD_POINT_LIGHT, "*point_light" },
			{ WORD_LIGHT_TYPE, "*light_type" },
			{ WORD_COLOR, "*color" },
			{ WORD_DISTANCE, "*distance" },
			{ WORD_ENERGY, "*energy" },
			{ WORD_FALLOFF_TYPE, "*fallof_type" },
			{ WORD_LINEAR_ATTENUATION, "*linear_attenuation" },
			{ WORD_QUADRATIC_ATTENUATION, "*quadratic_attenuation" },
			{ WORD_MATERIAL_REF, "*material_ref" },
			{ WORD_ACTIONS_REF, "*actions_ref" },
			{ WORD_ACTION_REF, "*action_ref" },
			{ WORD_CAMERA, "*camera" },
			{ WORD_FOV, "*fov" },
			{ WORD_NEAR_PLANE, "*near" },
			{ WORD_FAR_PLANE, "*far" },
			{ WORD_FOCUS, "*focus" },
			{ WORD_ORTHO_SCALE, "*ortho_scale" },
			{ WORD_COLLISION_MESH, "*collision_mesh" },
			{ WORD_LOCATION_INDOOR, "*location_indoor" },
			{ WORD_CONVEX_MESH, "*convex_mesh" },
			{ WORD_MATERIAL_NODE, "*material_node" },
			{ WORD_TRANSFORM_NODE, "*transform_node" },
			{ WORD_TRANSFORM, "*transform" },
			{ WORD_PORTAL, "*porta" },
			{ WORD_PORTAL_NODE, "*portal_node" },
			{ WORD_STATIC_MESH, "*static_mesh" },
			{ WORD_FACE_NORMALS, "*face_normals" },
			{ WORD_BONE_NODE, "*bone_node" },
			{ WORD_MAPDESCTEXT, "MAPDESCTEXT" },
			{ WORD_REF, "*ref" },
			{ WORD_RAW_DATA_SOURCE, "*raw_data_source" },
			{ WORD_NUM_BLOCKS, "*num_blocks" },
			{ WORD_BLOCK_SCALE, "*block_scale" },
			{ WORD_BLOCK_SIZE, "*block_size" },
			{ WORD_HEIGHT_SCALE, "*height_scale" },
			{ WORD_WORLD_ORIGIN, "*world_origin" },
			{ WORD_CELL, "*cel" },
			{ WORD_POINT, "*point" },
			{ WORD_SPLINE, "*spline" },
			{ WORD_POSITION, "*position" },
			{ WORD_WEIGHT, "*weight" },
			{ WORD_SCALE, "*scale" },
			{ WORD_IMAGE, "*image" },
			{ WORD_SPECULAR_INTENSITY_MAP, "*specular_intensity_map" },
			{ WORD_ARMATURETEXT, "ARMATURETEXT" },
			{ WORD_ACTIONTEXT, "ACTIONTEXT" },
			{ WORD_STATICMESHTEXT, "STATICMESHTEXT" },
			{ WORD_MATERIALTEXT, "MATERIALTEXT" },
			{ WORD_NAVIMESHTEXT, "NAVIMESHTEXT" },
			{ WORD_PATHTEXT, "PATHTEXT" },
			{ WORD_RIVERTEXT, "RIVERTEXT" },
			{ WORD_SCENETEXT, "SCENETEXT" },
			{ WORD_SUNTEXT, "SUNTEXT" },
			{ WORD_TERRAINTEXT, "SUNTEXT" },
			{ WORD_SUN, "*sun" },
			{ WORD_SUN_NODE, "*sun_node" },
			{ WORD_NAVIMESH_NODE, "*navi_mesh_node" },
			{ WORD_PATH_NODE, "*path_node" },
			{ WORD_TERRAIN_NODE, "*terrain_node" },
			{ WORD_RIVER_NODE, "*river_node" },
			{ WORD_MESH, "*mesh" },
			{ WORD_TERRAINTEXT, "TERRAINTEXT" },
			{ WORD_FLOW_SPEED, "*flow_speed" },
			{ WORD_FLOW_DIRECTION, "*flow_direction" },
			{ WORD_SKINMESH_TEXT, "SKINMESHTEXT" },
			{ WORD_NODE, "*node" },
			{ WORD_ROTATION, "*rotation" },
			{ WORD_ENTITY_NAME, "*entity_name" },
			{ WORD_DIRECTION, "*direction" },
			{ WORD_DIRLIGHTTEXT, "DIRLIGHTTEXT" },
			{ WORD_SPOTLIGHTTEXT, "SPOTLIGHTTEXT" },
			{ WORD_POINTLIGHTTEXT, "POINTLIGHTTEXT" },
			{ WORD_TRANSFORMTEXT, "TRANSFORMTEXT" },
			{ WORD_ARMATURE_SCHEMA, "*armature_schema" },
			{ WORD_ARMATURE_SCHEMA_TEXT, "ARMATURESCHEMATEXT" },
			{ WORD_FACTOR, "*factor" },
			{ WORD_DIFFUSE_TEXTURE_SLOT, "*diffuse_texture_slot" },
			{ WORD_NORMAL_TEXTURE_SLOT, "*normal_texture_slot" },
			{ WORD_SPECULAR_TEXTURE_SLOT, "*specular_texture_slot" },
			{ WORD_VERTEX_BONES_WEIGHTS, "*vertex_bones_weights" },
			{ WORD_VERTEX_INDEX, "*vertex_index" },
			{ WORD_BONES_WEIGHTS, "*bones_weights" },
			{ WORD_WEIGHTS, "*weights" },
			{ WORD_WEIGHTED_POINT, "*weighted_point" },
			{ WORD_CURVE_PATH, "*curve_path" },
			{ WORD_DIRECTIONAL_LIGHT, "*directional_light" },
			{ WORD_SPOT_LIGHT, "*spot_light" },
			{ WORD_VEC3F, "*vec3f" },
			{ WORD_VEC3FV, "*vec3fv" },
			{ WORD_VEC3IV, "*vec3iv" },
			{ WORD_VEC3VEC2VF, "*vec3vec2vf" },
			{ WORD_MATRIX4X4F, "*mat4x4f" },
			{ WORD_FLOAT, "*float" },
			{ WORD_STRING, "*string" },
			{ WORD_QUAT, "*quat" },
			{ WORD_SCENE_GRAPH, "*scene_graph" },
			{ WORD_CAMERATEXT, "CAMERATEXT" },
			{ WORD_PERSPECTIVE_CAMERA, "*perspective_camera" },
			{ WORD_ORTHO_CAMERA, "*ortho_camera" },
			{ WORD_PANORAMIC_CAMERA, "*panoramic_camera" },
			{ WORD_UP_VECTOR, "*up_vector" },
			{ WORD_UINT32, "*uint32" },
			{ WORD_TRACK_VEC3, "*track_vec3" },
			{ WORD_TRACK_VEC4, "*track_vec4" },
			{ WORD_TRACK_FLOAT, "*track_float" },
			{ WORD_TRACK_QUAT, "*track_quat" },
			{ WORD_TRACK_MAT4, "*track_mat4" },
			{ WORD_KEYS, "*keys" },
			{ WORD_INDEX, "*index" },
			{ WORD_ARMATURE_MATRIX, "*armature_matrix" }
	};

    KeywordCode ParseKeyword(const Core::String& word);
	const Core::String GetKeyword(KeywordCode code);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_KEY_WORDS
