#ifndef _H_PUNK_OPENGL_CONFIGER
#define _H_PUNK_OPENGL_CONFIGER

#include <cstdint>
#include <config.h>
#include <graphics/primitives/vertex.h>
#include <graphics/primitives/vertex_component.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		template<typename V, typename T, typename ... Args>
		struct AttributeConfigure : public AttributeConfigure < V, Args > {
			AttributeConfigure() {
				GL_CALL(glVertexAttribPointer(T::Slot(), T::Components(), GL_FLOAT, GL_FALSE, sizeof(V),
					(void*)Offset<V, T>::Value()));
				GL_CALL(glEnableVertexAttribArray(T::Slot()));
			}
		};
	}
}
PUNK_ENGINE_END
//
//namespace Graphics {
//    namespace OpenGL {
//
//		template<typename VertexType> class AttributeConfiger;
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position>>
//		{
//			typedef Vertex<VertexComponent::Position> CurrentVertex;			
//		public:
//
//            AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Texture0>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Texture0> CurrentVertex;			
//		public:
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Color>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Color> CurrentVertex;			
//		public:
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position,
//			VertexComponent::Normal>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Normal> CurrentVertex;
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Normal, 
//			VertexComponent::Texture0>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> CurrentVertex;
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Color, 
//			VertexComponent::Texture0>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0> CurrentVertex;
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Normal, 
//			VertexComponent::Texture0, 
//			VertexComponent::Flag>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0, VertexComponent::Flag> CurrentVertex;
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position,
//			VertexComponent::Texture0,
//			VertexComponent::Flag,
//			VertexComponent::Color>>
//		{
//			typedef Vertex<VertexComponent::Position,
//				VertexComponent::Texture0,
//				VertexComponent::Flag,
//				VertexComponent::Color> CurrentVertex;			
//
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position,
//			VertexComponent::Normal,
//			VertexComponent::Tangent, 
//			VertexComponent::Bitangent, 
//			VertexComponent::Texture0>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Tangent, VertexComponent::Bitangent, VertexComponent::Texture0> CurrentVertex;
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//
//		template<> 
//		class AttributeConfiger<
//			Vertex<
//			VertexComponent::Position, 
//			VertexComponent::Normal, 
//			VertexComponent::Tangent, 
//			VertexComponent::Bitangent, 
//			VertexComponent::Texture0, 
//			VertexComponent::BoneID,
//			VertexComponent::BoneWeight>>
//		{
//			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Tangent, VertexComponent::Bitangent, VertexComponent::Texture0, VertexComponent::BoneID, VertexComponent::BoneWeight> CurrentVertex;
//
//		public:
//
//			AttributeConfiger(int64_t available);
//		};
//	}
//}


#endif
