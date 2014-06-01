#ifndef _H_READER_POLICY
#define _H_READER_POLICY

#include <config.h>
#include <images/error/module.h>
#include "image_file_types.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {
	template<ImageFileType Type> struct ReaderPolicy {
		static bool CanDecode(Core::Buffer& buffer) {
			return false;
		}

		static void DecodeBuffer(Core::Buffer& buffer, IImage** image) {
			throw Error::ImageException("Not implemented");
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_READER_POLICY