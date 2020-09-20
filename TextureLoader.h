// TextureLoader.h: interface for the TextureLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURELOADER_H__D9266A69_A8ED_4AD7_B417_0579E81E2433__INCLUDED_)
#define AFX_TEXTURELOADER_H__D9266A69_A8ED_4AD7_B417_0579E81E2433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TextureLoader  
{
public:
	TextureLoader();
	virtual ~TextureLoader();

};

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char * loadBMPRaw(const char * filename, 
	unsigned int* outWidth, unsigned int* outHeight, 
	int flipY, int flipToBGR);

extern int dumpBMPRaw(const char *filename,
	unsigned char * data, unsigned int width, unsigned int height, 
	int flipY);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_TEXTURELOADER_H__D9266A69_A8ED_4AD7_B417_0579E81E2433__INCLUDED_)
