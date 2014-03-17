#include <math/vec4.h>
#include <graphics/opengl/module.h>
#include "gl_attribute_configer.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        AttributeConfiger<Vertex<VertexComponent::Position>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
            VertexComponent::Texture0>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{					
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
				
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
            VertexComponent::Color>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{					
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE
                    , sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	color
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Color::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

        AttributeConfiger<Vertex<VertexComponent::Position, VertexComponent::Normal>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
            VertexComponent::Texture0>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();

            std::int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Color, 
            VertexComponent::Texture0>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();

            std::int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	normal
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal,
			VertexComponent::Texture0, 
            VertexComponent::Flag>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0, VertexComponent::Flag>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glVertexAttribPointer(VertexComponent::Flag::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::FlagOffset()));	//	flag
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position,
			VertexComponent::Texture0,
			VertexComponent::Flag,
            VertexComponent::Color>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	color
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	color
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset()));	//	color
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture
                GL_CALL(glVertexAttribPointer(VertexComponent::Flag::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::FlagOffset()));	//	flag
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
            VertexComponent::Texture0>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

            if (components == Vertex<VertexComponent::Position>::Value()) {
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
            }
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Tangent
				, VertexComponent::Bitangent
				, VertexComponent::Texture0>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset()));	//	tangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset()));	//	bitangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Tangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Bitangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
			VertexComponent::Texture0, 
			VertexComponent::BoneID,
            VertexComponent::BoneWeight>>::AttributeConfiger(std::int64_t available)
		{
            static const std::int64_t Code = CurrentVertex::Value();
            std::int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Tangent
				, VertexComponent::Bitangent
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset()));	//	tangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset()));	//	bitangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight

                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Tangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Bitangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
            }
            else if (components == Vertex<VertexComponent::Position
                                    , VertexComponent::Normal
                                    , VertexComponent::Tangent
                                    , VertexComponent::Bitangent
                                    , VertexComponent::Texture0>::Value())
            {
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset()));	//	tangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset()));	//	bitangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Tangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Bitangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
            }
            else
                throw OpenGLException(L"Vertex do not support such render context");
        }
    }
}
PUNK_ENGINE_END
