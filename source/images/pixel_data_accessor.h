#ifndef _H_PIXEL_DATA_ACCESSOR
#define _H_PIXEL_DATA_ACCESSOR

#include <config.h>
#include "formats.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	template<ImageFormat format> struct PixelDataAccessor;

	template<>
	struct PixelDataAccessor < ImageFormat::RGBA > {

		PixelDataAccessor(void*& pixel_address)
			: m_pixel{ pixel_address } {}

		void Set(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint32_t a) {
			SetR(r); SetG(g); SetB(b); SetA(a);
		}

		void Get(std::uint8_t& r, std::uint8_t& g, std::uint8_t& b, std::uint32_t& a) {
			r = GetR(); g = GetG(); b = GetB(); a = GetA();
		}

		std::uint8_t GetR() const {
			return *((std::uint8_t*)m_pixel + 0);
		}

		std::uint8_t GetG() const {
			return *((std::uint8_t*)m_pixel + 1);
		}

		std::uint8_t GetB() const {
			return *((std::uint8_t*)m_pixel + 2);
		}

		std::uint8_t GetA() const {
			return *((std::uint8_t*)m_pixel + 3);
		}

		void SetR(std::uint8_t value) {
			*((std::uint8_t*)m_pixel + 0) = value;
		}

		void SetG(std::uint8_t value) {
			*((std::uint8_t*)m_pixel + 1) = value;
		}

		void SetB(std::uint8_t value) {
			*((std::uint8_t*)m_pixel + 2) = value;
		}

		void SetA(std::uint8_t value) {
			*((std::uint8_t*)m_pixel + 3) = value;
		}

	private:
		void*& m_pixel;
	};

}
PUNK_ENGINE_END

#endif	//	_H_PIXEL_DATA_ACCESSOR