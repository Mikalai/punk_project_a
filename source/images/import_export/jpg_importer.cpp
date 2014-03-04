#include <fstream>
#include <istream>
#include <ostream>
#include "string/module.h"
#include "system/logger/module.h"

#include "jpg_importer.h"
#include "images/internal_images/image_impl.h"
#include <stdio.h>
#include <memory.h>

#ifdef USE_LIB_JPEG
#include "libjpeg/jpeglib.h"
#include "libjpeg/jerror.h"
#include <setjmp.h>
#endif  //  USE_LIB_JPEG

PUNK_ENGINE_BEGIN
namespace Image
{
	JpgImporter::JpgImporter()
		: Importer()
    {
#ifdef USE_LIB_JPEG
        jpeg_decompress_struct s;
        s.src = nullptr;
#endif
    }

#ifdef USE_LIB_JPEG
	struct my_error_mgr {
		struct jpeg_error_mgr pub;	/* "public" fields */

		jmp_buf setjmp_buffer;	/* for return to caller */
	};

	typedef struct my_error_mgr * my_error_ptr;

	/*
	* Here's the routine that will replace the standard error_exit method:
	*/

	METHODDEF(void)
		my_error_exit (j_common_ptr cinfo)
	{
		/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
		my_error_ptr myerr = (my_error_ptr) cinfo->err;

		/* Always display the message. */
		/* We could postpone this until after returning, if we chose. */
		(*cinfo->err->output_message) (cinfo);

		/* Return control to the setjmp point */
		longjmp(myerr->setjmp_buffer, 1);
	}

	typedef struct
	{
		struct jpeg_source_mgr pub;	/* public fields */
		std::istream* stream;
		JOCTET * buffer;		/* start of buffer */
		boolean start_of_file;
	} my_source_mgr;

	typedef my_source_mgr * my_src_ptr;

#define INPUT_BUF_SIZE  4096	/* choose an efficiently fread'able size */

	/*
	* Initialize source --- called by jpeg_read_header
	* before any data is actually read.
	*/

	METHODDEF(void) init_source (j_decompress_ptr cinfo)
	{
		my_src_ptr src = (my_src_ptr) cinfo->src;

		/* We reset the empty-input-file flag for each image,
		* but we don't clear the input buffer.
		* This is correct behavior for reading a series of images from one source.
		*/
		src->start_of_file = TRUE;
	}

	METHODDEF(void) init_mem_source (j_decompress_ptr cinfo)
	{
		/* no work necessary here */
	}


	/*
	* Fill the input buffer --- called whenever buffer is emptied.
	*
	* In typical applications, this should read fresh data into the buffer
	* (ignoring the current state of next_input_byte & bytes_in_buffer),
	* reset the pointer & count to the start of the buffer, and return TRUE
	* indicating that the buffer has been reloaded.  It is not necessary to
	* fill the buffer entirely, only to obtain at least one more byte.
	*
	* There is no such thing as an EOF return.  If the end of the file has been
	* reached, the routine has a choice of ERREXIT() or inserting fake data into
	* the buffer.  In most cases, generating a warning message and inserting a
	* fake EOI marker is the best course of action --- this will allow the
	* decompressor to output however much of the image is there.  However,
	* the resulting error message is misleading if the real problem is an empty
	* input file, so we handle that case specially.
	*
	* In applications that need to be able to suspend compression due to input
	* not being available yet, a FALSE return indicates that no more data can be
	* obtained right now, but more may be forthcoming later.  In this situation,
	* the decompressor will return to its caller (with an indication of the
	* number of scanlines it has read, if any).  The application should resume
	* decompression after it has loaded more data into the input buffer.  Note
	* that there are substantial restrictions on the use of suspension --- see
	* the documentation.
	*
	* When suspending, the decompressor will back up to a convenient restart point
	* (typically the start of the current MCU). next_input_byte & bytes_in_buffer
	* indicate where the restart point will be if the current call returns FALSE.
	* Data beyond this point must be rescanned after resumption, so move it to
	* the front of the buffer rather than discarding it.
	*/

	METHODDEF(boolean)
		fill_input_buffer (j_decompress_ptr cinfo)
	{
		my_src_ptr src = (my_src_ptr) cinfo->src;
		size_t nbytes;

		src->stream->read((char*)src->buffer, INPUT_BUF_SIZE);
		nbytes = (size_t)src->stream->gcount();

        if (nbytes <= 0) {
			if (src->start_of_file)	/* Treat empty input file as fatal error */
				ERREXIT(cinfo, JERR_INPUT_EMPTY);
			WARNMS(cinfo, JWRN_JPEG_EOF);
			/* Insert a fake EOI marker */
			src->buffer[0] = (JOCTET) 0xFF;
			src->buffer[1] = (JOCTET) JPEG_EOI;
			nbytes = 2;
		}

		src->pub.next_input_byte = src->buffer;
		src->pub.bytes_in_buffer = nbytes;
		src->start_of_file = FALSE;

		return TRUE;
	}

	METHODDEF(boolean) fill_mem_input_buffer (j_decompress_ptr cinfo)
	{
		static const JOCTET mybuffer[4] = {
			(JOCTET) 0xFF, (JOCTET) JPEG_EOI, 0, 0
		};

		/* The whole JPEG data is expected to reside in the supplied memory
		* buffer, so any request for more data beyond the given buffer size
		* is treated as an error.
		*/
		WARNMS(cinfo, JWRN_JPEG_EOF);

		/* Insert a fake EOI marker */

		cinfo->src->next_input_byte = mybuffer;
		cinfo->src->bytes_in_buffer = 2;

		return TRUE;
	}


	/*
	* Skip data --- used to skip over a potentially large amount of
	* uninteresting data (such as an APPn marker).
	*
	* Writers of suspendable-input applications must note that skip_input_data
	* is not granted the right to give a suspension return.  If the skip extends
	* beyond the data currently in the buffer, the buffer can be marked empty so
	* that the next read will cause a fill_input_buffer call that can suspend.
	* Arranging for additional bytes to be discarded before reloading the input
	* buffer is the application writer's problem.
	*/

	METHODDEF(void) skip_input_data (j_decompress_ptr cinfo, long num_bytes)
	{
		struct jpeg_source_mgr * src = cinfo->src;

		/* Just a dumb implementation for now.  Could use fseek() except
		* it doesn't work on pipes.  Not clear that being smart is worth
		* any trouble anyway --- large skips are infrequent.
		*/
		if (num_bytes > 0) {
			while (num_bytes > (long) src->bytes_in_buffer) {
				num_bytes -= (long) src->bytes_in_buffer;
				(void) (*src->fill_input_buffer) (cinfo);
				/* note we assume that fill_input_buffer will never return FALSE,
				* so suspension need not be handled.
				*/
			}
			src->next_input_byte += (size_t) num_bytes;
			src->bytes_in_buffer -= (size_t) num_bytes;
		}
	}


	/*
	* An additional method that can be provided by data source modules is the
	* resync_to_restart method for error recovery in the presence of RST markers.
	* For the moment, this source module just uses the default resync method
	* provided by the JPEG library.  That method assumes that no backtracking
    * is possible.
	*/


	/*
	* Terminate source --- called by jpeg_finish_decompress
	* after all data has been read.  Often a no-op.
	*
	* NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
	* application must deal with any cleanup that should happen even
	* for error exit.
	*/

	METHODDEF(void) term_source (j_decompress_ptr cinfo)
	{
		/* no work necessary here */
	}


	/*
	* Prepare for input from a stdio stream.
	* The caller must have already opened the stream, and is responsible
	* for closing it after finishing decompression.
	*/

	GLOBAL(void) jpeg_stl_src (j_decompress_ptr cinfo, std::istream* infile)
	{
		my_src_ptr src;

		/* The source object and input buffer are made permanent so that a series
		* of JPEG images can be read from the same file by calling jpeg_stdio_src
		* only before the first one.  (If we discarded the buffer at the end of
		* one image, we'd likely lose the start of the next one.)
		* This makes it unsafe to use this manager and a different source
		* manager serially with the same JPEG object.  Caveat programmer.
		*/
		if (cinfo->src == NULL) {	/* first time for this JPEG object? */
			cinfo->src = (struct jpeg_source_mgr *)
				(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				sizeof(my_source_mgr));
			src = (my_src_ptr) cinfo->src;
			src->buffer = (JOCTET *)
				(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				INPUT_BUF_SIZE * sizeof(JOCTET));
		}

		src = (my_src_ptr) cinfo->src;
		src->pub.init_source = init_source;
		src->pub.fill_input_buffer = fill_input_buffer;
		src->pub.skip_input_data = skip_input_data;
		src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
		src->pub.term_source = term_source;
		src->stream = infile;
		src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
		src->pub.next_input_byte = NULL; /* until buffer loaded */
	}


//	/*
//	* Prepare for input from a supplied memory buffer.
//	* The buffer must contain the whole JPEG data.
//	*/

//	GLOBAL(void)
//		jpeg_mem_src (j_decompress_ptr cinfo,
//		unsigned char * inbuffer, unsigned long insize)
//	{
//		struct jpeg_source_mgr * src;

//		if (inbuffer == NULL || insize == 0)	/* Treat empty input as fatal error */
//			ERREXIT(cinfo, JERR_INPUT_EMPTY);

//		/* The source object is made permanent so that a series of JPEG images
//		* can be read from the same buffer by calling jpeg_mem_src only before
//		* the first one.
//		*/
//		if (cinfo->src == NULL) {	/* first time for this JPEG object? */
//			cinfo->src = (struct jpeg_source_mgr *)
//				(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
//				sizeof(struct jpeg_source_mgr));
//		}

//		src = cinfo->src;
//		src->init_source = init_mem_source;
//		src->fill_input_buffer = fill_mem_input_buffer;
//		src->skip_input_data = skip_input_data;
//		src->resync_to_restart = jpeg_resync_to_restart; /* use default method */
//		src->term_source = term_source;
//		src->bytes_in_buffer = (size_t) insize;
//		src->next_input_byte = (JOCTET *) inbuffer;
//	}
#endif  //  USE_LIB_JPEG

	bool JpgImporter::Load(std::istream& stream, Image* image)
	{
#ifdef USE_LIB_JPEG
        jpeg_decompress_struct cinfo;        
        my_error_mgr jerr;

		jpeg_create_decompress(&cinfo);
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = my_error_exit;

		jpeg_stl_src(&cinfo, &stream);
		jpeg_read_header(&cinfo, TRUE);
		jpeg_start_decompress(&cinfo);

		int output_width = cinfo.output_width;
		int output_height = cinfo.output_height;
		int out_color_components = cinfo.out_color_components;
		int output_components = cinfo.output_components;
		int actual_number_of_colors	= cinfo.actual_number_of_colors;

		ImageFormat format;
		if (output_components == 1)
			format = ImageFormat::IMAGE_FORMAT_ALPHA;
		else if (output_components == 3)
			format = ImageFormat::IMAGE_FORMAT_RGB;
		else
		{
			jpeg_destroy_decompress(&cinfo);
            throw Error::ImageException("Bad image format");
            return false;
		}

        image->Create(output_width, output_height, output_components, ComponentType::UnsignedByte, format);

		int row_stride = cinfo.output_width * cinfo.output_components;
		/* Make a one-row-high sample array that will go away when done with image */
		JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

        unsigned char* dst = (unsigned char*)image->GetData() + row_stride * (cinfo.output_height - 1);
		while (cinfo.output_scanline < cinfo.output_height)
		{
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)buffer, 1);
			memcpy(dst, *buffer, row_stride);
			dst -= row_stride;
		}

		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);

		return true;
		#else
        (void)stream; (void)image;
        throw System::Error::PunkNotImplemented(L"Can't work with jpeg files, cause jpeg lib was not used");
        #endif  //  USE_LIB_JPEG
    }

    bool JpgImporter::Load(Core::Buffer *mem, Image *image)
    {
#ifdef USE_LIB_JPEG
        jpeg_decompress_struct cinfo;        
        my_error_mgr jerr;

        jpeg_create_decompress(&cinfo);
        cinfo.err = jpeg_std_error(&jerr.pub);
        jerr.pub.error_exit = my_error_exit;

        jpeg_mem_src(&cinfo, (unsigned char*)mem->Data(), (unsigned long)mem->GetSize());
        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);

        int output_width = cinfo.output_width;
        int output_height = cinfo.output_height;
        int out_color_components = cinfo.out_color_components;
        int output_components = cinfo.output_components;
        int actual_number_of_colors	= cinfo.actual_number_of_colors;

        ImageFormat format;
        if (output_components == 1)
            format = ImageFormat::IMAGE_FORMAT_ALPHA;
        else if (output_components == 3)
            format = ImageFormat::IMAGE_FORMAT_RGB;
        else
        {
            jpeg_destroy_decompress(&cinfo);
            System::GetDefaultLogger()->Error("Bad image format");
            return false;
        }

        image->Create(output_width, output_height, output_components, ComponentType::UnsignedByte, format);

        int row_stride = cinfo.output_width * cinfo.output_components;
        /* Make a one-row-high sample array that will go away when done with image */
        JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

        unsigned char* dst = (unsigned char*)image->GetData() + row_stride * (cinfo.output_height - 1);
        while (cinfo.output_scanline < cinfo.output_height)
        {
            jpeg_read_scanlines(&cinfo, (JSAMPARRAY)buffer, 1);
            memcpy(dst, *buffer, row_stride);
            dst -= row_stride;
        }

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);

        return true;
        #else
        (void)mem; (void)image;
        throw System::Error::PunkNotImplemented(L"Can't work with jpeg files, cause jpeg lib was not used");
        #endif  //  USE_LIB_JPEG
    }

    bool JpgImporter::Load(const Core::String& file)
	{
        std::ifstream stream((char*)file.ToUtf8().Data(), std::ios_base::binary);
		if (!stream.is_open())
		{
            System::GetDefaultLogger()->Error(L"Can't open file: " + file);
			return false;
		}
		Load(stream, this);
		stream.close();
		return true;
	}
}
PUNK_ENGINE_END
