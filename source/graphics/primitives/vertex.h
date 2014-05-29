#ifndef _H_PUNK_GPU_VERTEX
#define _H_PUNK_GPU_VERTEX

#include <cstdint>
#include <cstddef>
#include <config.h>
#include <math/vec4.h>
#include "vertex_component.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{

	template<std::uint32_t _offset, class Component> struct ComponentAccessor;

	template<std::uint32_t _offset>
	struct ComponentAccessor <_offset, VertexComponent::Position > {
		Math::vec4 m_position;
		static constexpr std::uint32_t PositionOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor <_offset, VertexComponent::Color > {
		Math::vec4 m_color;
		static constexpr std::uint32_t ColorOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Normal > {
		Math::vec4 m_normal;
		static constexpr std::uint32_t NormalOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Tangent > {
		Math::vec4 m_tangent;
		static constexpr std::uint32_t TangentOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Bitangent > {
		Math::vec4 m_bitangent;
		static constexpr std::uint32_t BitangentOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Texture0 > {
		Math::vec4 m_texture0;
		static constexpr std::uint32_t Texture0Offset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Texture1 > {
		Math::vec4 m_texture1;
		static constexpr std::uint32_t Texture1Offset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Texture2 > {
		Math::vec4 m_texture2;
		static constexpr std::uint32_t Texture2Offset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Texture3 > {
		Math::vec4 m_texture3;
		static constexpr std::uint32_t Texture3Offset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::BoneID > {
		Math::vec4 m_bone_id;
		static constexpr std::uint32_t BoneId0Offset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::BoneWeight > {
		Math::vec4 m_bone_weight;
		static constexpr std::uint32_t BoneWeightOffset() {
			return _offset;
		}
	};

	template<std::uint32_t _offset>
	struct ComponentAccessor < _offset, VertexComponent::Flag > {
		Math::vec4 m_flag;
		static constexpr std::uint32_t FlagOffset() {
			return _offset;
		}
	};

	template<class V, class C> struct Offset;

	template<class V>
	struct Offset < V, VertexComponent::Position > {
		static constexpr int Value() {
			return V::PositionOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Normal > {
		static constexpr int Value() {
			return V::NormalOffset();
		}
	}; 

	template<class V>
	struct Offset < V, VertexComponent::Tangent > {
		static constexpr int Value() {
			return V::TangentOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Bitangent> {
		static constexpr int Value() {
			return V::BitangentOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Color > {
		static constexpr int Value() {
			return V::ColorOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Texture0 > {
		static constexpr int Value() {
			return V::Texture0Offset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Texture1 > {
		static constexpr int Value() {
			return V::Texture1Offset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Texture2 > {
		static constexpr int Value() {
			return V::Texture2Offset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Texture3 > {
		static constexpr int Value() {
			return V::Texture3Offset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::BoneID > {
		static constexpr int Value() {
			return V::BoneIdOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::BoneWeight > {
		static constexpr int Value() {
			return V::BoneWeightOffset();
		}
	};

	template<class V>
	struct Offset < V, VertexComponent::Flag > {
		static constexpr int Value() {
			return V::FlagOffset();
		}
	};

	template<size_t _offset, std::uint64_t _value, typename ... Components> struct VertexBuilder;

	template<size_t _offset, std::uint64_t _value, typename Component, typename ... Components>
	struct VertexBuilder<_offset, _value, Component, Components...> : public ComponentAccessor<_offset, Component>, public VertexBuilder < _offset + Component::Size(), _value | Component::Value(), Components...>{
	};

	template<size_t _offset, std::uint64_t _value>
	struct VertexBuilder<_offset, _value> {
		static constexpr std::int64_t Value() {
			return _value;
		}
	};

	template<typename ...Components>
	struct Vertex : public VertexBuilder <0, 0, Components... > {
		template<template<typename...> class T>
		using Type = T < Components... > ;
	};

//	template <typename T, typename M> M get_member_type(M T::*);
//	template <typename T, typename M> T get_class_type(M T::*);
//
//	template <typename T,
//		typename R,
//		R T::*M
//	>
//	constexpr std::size_t offset_of()
//	{
//		return reinterpret_cast<std::size_t>(&(((T*)0)->*M));
//	}
//
//#define OFFSET_OF(m) offset_of<decltype(get_class_type(m)), decltype(get_member_type(m)), m>()
//
//
//#ifdef offsetof
//#undef offsetof
//#define offsetof(T, M) OFFSET_OF(&T::M)
//#endif
//
	/**
		Ubervertex:
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
	/*template<typename... Components> struct Vertex;
	
	template<> struct Vertex<VertexComponent::Position>
	{
		typedef Vertex<VertexComponent::Position> T;

		Math::vec4 m_position;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value();
		}

        static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0>
	{
		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0> T;

		Math::vec4 m_position;
		Math::vec4 m_texture0;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Texture0::Value();
		}

        static constexpr std::size_t PositionOffset() { return offsetof(T, m_position); }
        static constexpr std::size_t Texture0Offset() { return offsetof(T, m_texture0); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal>
	{

		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
	};

	template<>
	struct Vertex<
		VertexComponent::Position,
		VertexComponent::Color>
	{
		typedef Vertex<VertexComponent::Position,
		VertexComponent::Color> T;

		Math::vec4 m_position;
		Math::vec4 m_color;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Color::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t ColorOffset() { return offsetof(T, m_color); }
	};

	template<>
	struct Vertex<
		VertexComponent::Position,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight>
	{
		typedef Vertex<VertexComponent::Position,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight> T;

		Math::vec4 m_position;
		Math::vec4 m_bone_id;
		Math::vec4 m_weight;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::BoneID::Value()
				| VertexComponent::BoneWeight::Value();
		}

		static size_t PositionOffset() { return offsetof(T, m_position); }
		static size_t BoneIDOffset() { return offsetof(T, m_bone_id); }
		static size_t BoneWeightOffset() { return offsetof(T, m_weight); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0>
	{

		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::Texture0::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
	};


	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Color,
		VertexComponent::Texture0>
	{
		typedef Vertex<VertexComponent::Position,
		VertexComponent::Color,
		VertexComponent::Texture0> T;

		Math::vec4 m_position;
		Math::vec4 m_color;
		Math::vec4 m_texture0;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Color::Value()
				| VertexComponent::Texture0::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t ColorOffset() { return offsetof(T, m_color); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0,
		VertexComponent::Flag>
	{
		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0,
		VertexComponent::Flag> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;
		Math::vec4 m_flag;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::Texture0::Value()
				| VertexComponent::Flag::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
		static constexpr size_t FlagOffset() { return offsetof(T, m_flag); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight>
	{

		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight> T;

		Math::vec4 m_position;
		Math::vec4 m_texture0;
		Math::vec4 m_bone_id;
		Math::vec4 m_bone_weight;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Texture0::Value()
				| VertexComponent::BoneID::Value()
				| VertexComponent::BoneWeight::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
		static constexpr size_t BoneIDOffset() { return offsetof(T, m_bone_id); }
		static constexpr size_t BoneWeightOffset() { return offsetof(T, m_bone_weight); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight>
	{

		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_bone_id;
		Math::vec4 m_bone_weight;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::BoneID::Value()
				| VertexComponent::BoneWeight::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t BoneIDOffset() { return offsetof(T, m_bone_id); }
		static constexpr size_t BoneWeightOffset() { return offsetof(T, m_bone_weight); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0,
		VertexComponent::Flag,
		VertexComponent::Color>
	{

		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Texture0,
		VertexComponent::Flag,
		VertexComponent::Color> T;

		Math::vec4 m_position;
		Math::vec4 m_texture0;
		Math::vec4 m_flag;
		Math::vec4 m_color;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Texture0::Value()
				| VertexComponent::Flag::Value()
				| VertexComponent::Color::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
		static constexpr size_t FlagOffset() { return offsetof(T, m_flag); }
		static constexpr size_t ColorOffset() { return offsetof(T, m_color); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Tangent,
		VertexComponent::Bitangent,
		VertexComponent::Texture0>
	{
		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Tangent,
		VertexComponent::Bitangent,
		VertexComponent::Texture0> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::Tangent::Value()
				| VertexComponent::Bitangent::Value()
				| VertexComponent::Texture0::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t TangentOffset() { return offsetof(T, m_tangent); }
		static constexpr size_t BitangentOffset() { return offsetof(T, m_bitangent); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight>
	{
		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;
		Math::vec4 m_bones_id;
		Math::vec4 m_bone_weights;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::Texture0::Value()
				| VertexComponent::BoneID::Value()
				| VertexComponent::BoneWeight::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
		static constexpr size_t BoneIDOffset() { return offsetof(T, m_bones_id); }
		static constexpr size_t BoneWeightOffset() { return offsetof(T, m_bone_weights); }
	};

	template<> struct Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Tangent,
		VertexComponent::Bitangent,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight>
	{
		typedef Vertex<
		VertexComponent::Position,
		VertexComponent::Normal,
		VertexComponent::Tangent,
		VertexComponent::Bitangent,
		VertexComponent::Texture0,
		VertexComponent::BoneID,
		VertexComponent::BoneWeight> T;

		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;
		Math::vec4 m_bones_id;
		Math::vec4 m_bone_weights;

        static constexpr std::int64_t Value()
		{
			return VertexComponent::Position::Value()
				| VertexComponent::Normal::Value()
				| VertexComponent::Tangent::Value()
				| VertexComponent::Bitangent::Value()
				| VertexComponent::Texture0::Value()
				| VertexComponent::BoneID::Value()
				| VertexComponent::BoneWeight::Value();
		}

		static constexpr size_t PositionOffset() { return offsetof(T, m_position); }
		static constexpr size_t NormalOffset() { return offsetof(T, m_normal); }
		static constexpr size_t TangentOffset() { return offsetof(T, m_tangent); }
		static constexpr size_t BitangentOffset() { return offsetof(T, m_bitangent); }
		static constexpr size_t Texture0Offset() { return offsetof(T, m_texture0); }
		static constexpr size_t BoneIDOffset() { return offsetof(T, m_bones_id); }
		static constexpr size_t BoneWeightOffset() { return offsetof(T, m_bone_weights); }
	};	
	*/
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_VERTEX
