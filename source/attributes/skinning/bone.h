#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include <config.h>
#include <math/mat4.h>
#include <string/string.h>
#include "types.h"
#include "ibone.h"

#include <vector>
#include <map>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class AnimationMixer;

	class PUNK_ENGINE_LOCAL Bone : public IBone
	{
	public:

		Bone();
		Bone(const Bone&) = delete;
		Bone& operator = (const Bone&) = delete;
		virtual ~Bone();

		void SetIndex(std::uint32_t value) override;
		std::uint32_t GetIndex() const override;
		void SetName(const Core::String& value) override;
		const Core::String& GetName() const override;
		void SetLength(float value) override;
		float GetLength() const override;
		void SetRestMatrix(const Math::mat4& value) override;
		const Math::mat4& GetRestMatrix() const override;
		void SetParent(std::uint32_t value) override;
		std::uint32_t GetParent() const override;
		bool HasParent() const override;
		void AddChild(std::uint32_t index) override;
		std::uint32_t GetChildrenCount() const override;
		std::uint32_t GetChild(std::uint32_t index) override;

	private:		

		std::uint32_t m_index{ std::numeric_limits<std::uint32_t>::infinity() };
		std::uint32_t m_parent{ std::numeric_limits<std::uint32_t>::infinity() };
		Math::mat4 m_rest_matrix;
		Core::String m_name;
		float m_length;
		std::vector<std::uint32_t> m_children;
	};    
}
PUNK_ENGINE_END

#endif
