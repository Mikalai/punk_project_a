#ifndef NEW_NODE_PNG_H
#define NEW_NODE_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char new_node_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 
	0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 
	0x7A, 0x7A, 0xF4, 0x00, 0x00, 0x00, 0x04, 0x73, 0x42, 0x49, 
	0x54, 0x08, 0x08, 0x08, 0x08, 0x7C, 0x08, 0x64, 0x88, 0x00, 
	0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x11, 
	0x09, 0x00, 0x00, 0x11, 0x09, 0x01, 0xC0, 0xE5, 0xA2, 0x18, 
	0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 
	0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x77, 0x77, 0x77, 
	0x2E, 0x69, 0x6E, 0x6B, 0x73, 0x63, 0x61, 0x70, 0x65, 0x2E, 
	0x6F, 0x72, 0x67, 0x9B, 0xEE, 0x3C, 0x1A, 0x00, 0x00, 0x01, 
	0x0B, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xED, 0x97, 0x31, 
	0x6A, 0xC3, 0x30, 0x14, 0x40, 0xDF, 0x97, 0x2A, 0x68, 0x6E, 
	0x60, 0x9A, 0xBD, 0x53, 0x86, 0x52, 0xC5, 0x2E, 0xF8, 0x06, 
	0xCD, 0x3D, 0x3A, 0x65, 0xCE, 0x19, 0xBA, 0x64, 0xCD, 0xD4, 
	0x7B, 0x24, 0x37, 0x30, 0x08, 0x47, 0xA5, 0x43, 0xA6, 0xEC, 
	0xEE, 0x15, 0x3C, 0x18, 0xF3, 0xBB, 0xD4, 0x60, 0xBA, 0x74, 
	0x09, 0xD6, 0xE2, 0xB7, 0x49, 0x08, 0xDE, 0x03, 0xC1, 0x87, 
	0x2F, 0xAA, 0x4A, 0x4A, 0x4C, 0x52, 0x3B, 0x70, 0x37, 0x3E, 
	0x94, 0x65, 0xB9, 0xE8, 0xBA, 0xEE, 0x59, 0x55, 0x3D, 0xF0, 
	0x70, 0x63, 0xD7, 0xB7, 0x88, 0x44, 0xE7, 0xDC, 0x67, 0x55, 
	0x55, 0xED, 0x70, 0x29, 0xC3, 0x17, 0xE4, 0x79, 0xFE, 0xAA, 
	0xAA, 0x1F, 0xC0, 0xF2, 0xC6, 0xE2, 0xBF, 0x34, 0x22, 0xF2, 
	0x56, 0xD7, 0xF5, 0x09, 0x7E, 0xBF, 0xC0, 0x7B, 0xBF, 0x55, 
	0xD5, 0xE3, 0x04, 0x72, 0x80, 0xA5, 0xAA, 0x1E, 0xBD, 0xF7, 
	0x5B, 0x00, 0x29, 0x8A, 0xE2, 0xB1, 0xEF, 0xFB, 0x2F, 0x60, 
	0x31, 0x81, 0x7C, 0x4C, 0x6B, 0xAD, 0x7D, 0xB2, 0x59, 0x96, 
	0xBD, 0x03, 0x2F, 0x13, 0xCB, 0x01, 0x9C, 0xAA, 0xDE, 0x1B, 
	0x60, 0x9D, 0x40, 0x3E, 0xB0, 0x36, 0xC0, 0x2A, 0x61, 0xC0, 
	0xCA, 0x00, 0x2E, 0x61, 0x80, 0x4B, 0x3E, 0x88, 0xE6, 0x80, 
	0x39, 0x60, 0x0E, 0x98, 0x03, 0xE6, 0x80, 0x39, 0xC0, 0x00, 
	0x5D, 0x42, 0x7F, 0x67, 0x80, 0x4B, 0xC2, 0x80, 0x8B, 0x01, 
	0xCE, 0x09, 0x03, 0xCE, 0xC6, 0x5A, 0xBB, 0x07, 0xDA, 0x7F, 
	0x9F, 0xDE, 0x9E, 0xD6, 0x5A, 0xBB, 0x37, 0x21, 0x84, 0xAB, 
	0xAA, 0xEE, 0xA6, 0xB6, 0xAB, 0xEA, 0x2E, 0x84, 0x70, 0x35, 
	0x00, 0x31, 0xC6, 0x83, 0x88, 0x6C, 0x80, 0x66, 0x02, 0x77, 
	0x23, 0x22, 0x9B, 0x18, 0xE3, 0x01, 0x46, 0x9B, 0x11, 0x24, 
	0x5E, 0xCD, 0x52, 0x91, 0x7C, 0x10, 0xFD, 0x00, 0xB2, 0x71, 
	0x61, 0x71, 0x45, 0x3A, 0xBE, 0x2D, 0x00, 0x00, 0x00, 0x00, 
	0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& new_node_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( new_node_png, sizeof( new_node_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //NEW_NODE_PNG_H
