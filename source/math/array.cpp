#include <vector>
#include "array.h"

PUNK_ENGINE_BEGIN
namespace Math {

	namespace __private {
		struct ArrayImpl : public std::vector < float > {
		};
	}

	Array::Array()
		: impl(new __private::ArrayImpl) {}

	Array::Array(const Array& value)
		: impl(new __private::ArrayImpl(*value.impl)) {}

	Array& Array::operator = (const Array& value) {
		Array temp(value);
		std::swap(*impl, *temp.impl);
		return *this;
	}

	float& Array::operator [] (std::size_t index) {
		return (*impl)[index];
	}

	const float& Array::operator [] (std::size_t index) const {
		return (*impl)[index];
	}

	std::size_t Array::size() const {
		return impl->size();
	}

	bool Array::empty() const {
		return impl->empty();
	}

	void Array::push_back(float value) {
		return impl->push_back(value);
	}

	void Array::pop_back() {
		impl->pop_back();
	}

	float Array::back() {
		return impl->back();
	}
}
PUNK_ENGINE_END
