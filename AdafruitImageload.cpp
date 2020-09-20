// AdafruitImageload.cpp: implementation of the AdafruitImageload class.
//
//////////////////////////////////////////////////////////////////////

#include "string.h"
#include "sdl_api.h"
#include "AdafruitImageload.h"
#include "TextureLoader.h"

void Palette::make_transparent(int index)
{
#if 1
	if (index == 0)
	{
		m_value0 = (0x00FFFFFF & m_value0);
	}
	else if (index == 1)
	{
		m_value1 = (0x00FFFFFF & m_value1);
	}
	else
	{
		// == 15
		m_value1 = (0x00FFFFFF & m_value1);
/*
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
*/
	}
#endif
}

void Palette::set(int index, unsigned int value)
{
	if (index == 0)
	{
		m_value0 = (0xFF000000 | value);
	}
	else if (index == 1)
	{
		m_value1 = (0xFF000000 | value);
	}
	else
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}
}

unsigned int Palette::get(int index)
{
	if (index == 0)
	{
		return m_value0;
	}
	else if (index == 1)
	{
		return m_value1;
	}
	else
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AdafruitImageload::AdafruitImageload(const char *filename, int bitmapType, int paletteType, Palette** pPalette)
:m_filename(filename)
,m_bitmapType(bitmapType)
,m_paletteType(paletteType)
{
	unsigned int outWidth = 0, outHeight = 0;
	unsigned char* pixels = NULL;
	char path[256] = {0};
	strcpy(path, ".");
	strcat(path, filename);
	pixels = loadBMPRaw(path, &outWidth, &outHeight, 1, 0);
	printf("[AdafruitImageload::AdafruitImageload]%s, %d, %d, %x\n", path, outWidth, outHeight, pixels);
	if (pixels == NULL)
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}

	*pPalette = new Palette();
	this->m_palette = *pPalette;
	m_width = outWidth;
	m_height = outHeight;
	if (m_width % 8 == 0)
	{
		m_widthByte = m_width / 8;
	}
	else
	{
		m_widthByte = m_width / 8 + 1;
	}
	m_pixels = (unsigned char *)calloc(m_widthByte * m_height, 1); //pixels;
	for (int j = 0; j < m_height; ++j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			unsigned char r = pixels[j * m_width * 3 + i * 3 + 0];
			unsigned char g = pixels[j * m_width * 3 + i * 3 + 1];
			unsigned char b = pixels[j * m_width * 3 + i * 3 + 2];
			unsigned int rgb = (r << 16) | (g << 8) | (b << 0);
			if (rgb == 0xffffff)
			{
				m_pixels[j * m_widthByte + i / 8] |= ((1 << (i % 8)) & 0xff);
				(*pPalette)->set(1, rgb);
			}
			else
			{
				m_pixels[j * m_widthByte + i / 8] &= (~(1 << (i % 8)) & 0xff);
				(*pPalette)->set(0, rgb);
			}
		}
	}
}

AdafruitImageload::~AdafruitImageload()
{

}

AdafruitImageload *AdafruitImageload::load(const char *filename, int bitmapType, int paletteType, Palette** pPalette)
{
	return new AdafruitImageload(filename, bitmapType, paletteType, pPalette);
}

int AdafruitImageload::get_width()
{
	return this->m_width;
}

int AdafruitImageload::get_height()
{
	return this->m_height;
}

Palette *AdafruitImageload::get_palette()
{
	return this->m_palette;
}

unsigned char *AdafruitImageload::get_pixels()
{
	return this->m_pixels;
}

int AdafruitImageload::get_width_byte()
{
	return this->m_widthByte;
}
