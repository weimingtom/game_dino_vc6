// AdafruitImageload.h: interface for the AdafruitImageload class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADAFRUITIMAGELOAD_H__5B132F2E_8510_4EB8_9703_19EFE7C31D1D__INCLUDED_)
#define AFX_ADAFRUITIMAGELOAD_H__5B132F2E_8510_4EB8_9703_19EFE7C31D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

class Palette
{
public:
	Palette() : m_value0(0), m_value1(0) {}
	virtual ~Palette() {}

	void make_transparent(int index);
	void set(int index, unsigned int value);
	unsigned int get(int index);

private:
	unsigned int m_value0;
	unsigned int m_value1;
};

//see https://github.com/adafruit/Adafruit_CircuitPython_ImageLoad
class AdafruitImageload  
{
public:
	AdafruitImageload(const char *filename, int bitmapType, int paletteType, Palette** pPalette);
	virtual ~AdafruitImageload();

	static AdafruitImageload *load(const char *filename, int bitmapType, int paletteType, Palette** pPalette);

	int get_width();
	int get_height();
	Palette *get_palette();
	unsigned char *get_pixels();
	int get_width_byte();

private:
	const char *m_filename;
	int m_bitmapType;
	int m_paletteType;

	int m_width;
	int m_widthByte;
	int m_height;
	unsigned char *m_pixels;
	Palette *m_palette;
};

#endif // !defined(AFX_ADAFRUITIMAGELOAD_H__5B132F2E_8510_4EB8_9703_19EFE7C31D1D__INCLUDED_)
