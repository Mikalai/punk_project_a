#ifndef _PUNK_GPU_VERTEX_COMPONENT
#define _PUNK_GPU_VERTEX_COMPONENT

#include <stdint.h>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	/*
	position	0
	normal		1
	tangent		2
	bitangent	3
	color		4
	texture0	5
	texture1	6
	texture2	7
	texture3	8
	bone id		9
	bone weight	10
	flags		11
	*/

	enum class VertexComponentType {
		No,
		Float,
		Uint32,
		Uint16
	};

	struct VertexComponent
	{
        struct NoComponent
		{
			static constexpr int64_t Value() { return 0; }
			static constexpr unsigned Slot() { return -1; }
			static constexpr VertexComponentType Type() { return VertexComponentType::No; }
			static constexpr int Components() { return -1; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Position
		{
			static constexpr int64_t Value() { return 1; }
			static constexpr unsigned Slot() { return 0; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Normal
		{
			static constexpr int64_t Value() { return 2; }
			static constexpr unsigned Slot() { return 1; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Tangent
		{
			static constexpr int64_t Value() { return 4; }
			static constexpr unsigned Slot() { return 2; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Bitangent
		{
			static constexpr int64_t Value() { return 8; }
			static constexpr unsigned Slot() { return 3; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Color
		{
			static constexpr int64_t Value() { return 1024; }
			static constexpr unsigned Slot() { return 4; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};


		struct Texture0
		{
			static constexpr int64_t Value() { return 16; }
			static constexpr unsigned Slot() { return 5; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Texture1
		{
			static constexpr int64_t Value() { return 32; }
			static constexpr unsigned Slot() { return 6; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Texture2
		{
			static constexpr int64_t Value() { return 64; }
			static constexpr unsigned Slot() { return 7; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Texture3
		{
			static constexpr int64_t Value() { return 128; }
			static constexpr unsigned Slot() { return 8; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct BoneID
		{
			static constexpr int64_t Value() { return 256; }
			static constexpr unsigned Slot() { return 9; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct BoneWeight
		{
			static constexpr int64_t Value() { return 512; }
			static constexpr unsigned Slot() { return 10; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};

		struct Flag
		{
			static constexpr int64_t Value() { return 2048; }
			static constexpr unsigned Slot() { return 11; }
			static constexpr VertexComponentType Type() { return VertexComponentType::Float; }
			static constexpr int Components() { return 4; }
			static constexpr bool NeedNormalization() { return false; }
		};
	};

}
PUNK_ENGINE_END

#endif	//	_PUNK_GPU_VERTEX_COMPONENT
