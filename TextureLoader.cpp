// TextureLoader.cpp: implementation of the TextureLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "TextureLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

unsigned char * loadBMPRaw(const char * filename, 
	unsigned int* outWidth, unsigned int* outHeight, 
	int flipY, int flipToBGR)
{
	unsigned char header[54] = {0};
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned char * data;
	unsigned int zeroByteSize = 0;
	FILE * file;

	if (!filename || !outWidth || !outHeight)
	{
		fprintf(stderr, "filename or outWidth or outHeight is NULL\n"); 
		return NULL;
	}
	*outWidth = -1;
	*outHeight = -1;
	file = fopen(filename, "rb");
	if (!file)
	{
		fprintf(stderr, "Open input bmp file error\n");
		return NULL;
	}
	if (fread(header, 1, sizeof(header), file) != 54)
	{ 
		fprintf(stderr, "Read input bmp file header error\n");
		fclose(file);
		return NULL;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		fprintf(stderr, "Not a correct BMP file (magic BM)\n");
		fclose(file);
		return NULL;
	}
	if (header[24 + 4] != 24 || header[24 + 5] != 0) //biBitCount
	{
		fprintf(stderr, "Not a correct BMP file (24bpp) \n");
		fclose(file);
		return NULL;
	}
	dataPos = (header[8 + 2]) | (header[8 + 3] << 8) | (header[8 + 4] << 16) | (header[8 + 5] << 24); //bfOffBits
	imageSize = (header[32 + 2]) | (header[32 + 3] << 8) | (header[32 + 4] << 16) | (header[32 + 5] << 24); //biSizeImage
	*outWidth = (header[16 + 2]) | (header[16 + 3] << 8) | (header[16 + 4] << 16) | (header[16 + 5] << 24); //biWidth
	*outHeight = (header[16 + 6]) | (header[16 + 7] << 8) | (header[16 + 8] << 16) | (header[16 + 9] << 24); //biHeight
	if (imageSize == 0)    
	{
		imageSize = (*outWidth) * (*outHeight) * 3;
	}
	zeroByteSize = (imageSize - (*outWidth) * (*outHeight) * 3) / (*outHeight);
	if (zeroByteSize < 0)
	{
		fprintf(stderr, "zeroByteSize < 0\n");
		fclose(file);
		return NULL;
	}
#ifdef _DEBUG
		fprintf(stderr, "[loadBMPRaw][%s]imageSize = %d >= (%d x %d x 3)\n", 
			filename, imageSize, (*outWidth), (*outHeight));
		fprintf(stderr, "[loadBMPRaw][%s]zeroByteSize = %d\n", 
			filename, zeroByteSize);
#endif
	if (dataPos == 0)
	{
		dataPos = 54;
	}
	data = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
	if (data == NULL)
	{
		fprintf(stderr, "Out of memory\n");
		fclose(file);
		return NULL;
	}
	//biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;
	if (zeroByteSize == 0)
	{
		if (imageSize != fread(data, 1, imageSize, file))
		{
			fprintf(stderr, "Read input bmp file data error\n");
			fclose(file);
			return NULL;
		}
	}
	else
	{
		unsigned int i;
		unsigned char * p = data;
		for (i = 0; i < *outHeight; i++)
		{
			unsigned int linesize = *outWidth * 3 + zeroByteSize;
			if (linesize != fread(p, 1, linesize, file))
			{
				fprintf(stderr, "Read input bmp file data error\n");
				fclose(file);
				return NULL;
			}
			p += *outWidth * 3;
		}
	}
	fclose(file);

	if (flipY)
	{
		unsigned char * tmpBuffer;
		int size;
		unsigned int i;
		size = (*outWidth) * 3;
		tmpBuffer = (unsigned char *)malloc((*outWidth) * 3 * sizeof(unsigned char));
		if (tmpBuffer == NULL)
		{
			fprintf(stderr, "Out of memory\n");
			return NULL;
		}
		for (i = 0; i < (*outHeight) / 2; i++)
		{
			memcpy(tmpBuffer, data + (*outWidth) * 3 * i, size);
			memcpy(data + (*outWidth) * 3 * i, data + (*outWidth) * 3 * ( (*outHeight) - i - 1), size);
			memcpy(data + (*outWidth) * 3 * ((*outHeight) - i - 1), tmpBuffer, size);
		}
		free(tmpBuffer);
	}
	if (flipToBGR)
	{
		unsigned int i, j;
		unsigned char * pPixel;
		unsigned char tmpChanel;
		for (i = 0; i < (*outHeight); i++)
		{
			for (j = 0; j < (*outWidth); j++)
			{
				pPixel = data + (*outWidth) * 3 * i + j * 3;
				tmpChanel = *pPixel;
				*pPixel = *(pPixel + 2);
				*(pPixel + 2) = tmpChanel;
			}
		}
	}
	return data;
}

int dumpBMPRaw(const char *filename,
	unsigned char * data, unsigned int width, unsigned int height, int flipY)
{
	FILE *fp = NULL;
	unsigned int imagesize = 0;
	unsigned int filesize = 0;
	unsigned char header[54] = {0};
	unsigned int zeroByteSize = 0;

	if (!filename)
	{
		fprintf(stderr, "filename is NULL\n"); 
		return 0;
	}
	zeroByteSize = 4 - ((width * 3) % 4);
	if (zeroByteSize == 4)
	{
		zeroByteSize = 0;
	}
	imagesize = (width * 3 + zeroByteSize) * height;

	filesize = imagesize + 56;
	header[0] = 0x42; // 'B'
	header[1] = 0x4D; // 'M'
	header[2] = filesize; // bytes num
	header[3] = filesize >> 8; //
	header[4] = filesize >> 16; //
	header[5] = filesize >> 24; //
	//printf("0x%0x, 0x%0x, 0x%0x, 0x%0x\n", header[2], header[3], header[4], header[5]);
	header[8 + 2] = 0x36; // data offset = 54 bfOffBits
	header[8 + 6] = 0x28;
	header[16 + 2] = width;
	header[16 + 3] = width >> 8;
	header[16 + 4] = width >> 16;
	header[16 + 5] = width >> 24;
	header[16 + 6] = height;
	header[16 + 7] = height >> 8;
	header[24 + 0] = height >> 16;
	header[24 + 1] = height >> 24;
	header[24 + 2] = 0x01; // biPlane = 1
	header[24 + 4] = 0x18; // biBitCount = 24
	header[32 + 2] = imagesize; // biSizeImage
	header[32 + 3] = imagesize >> 8; 
	header[32 + 4] = imagesize >> 16;
	header[32 + 5] = imagesize >> 24;
	header[32 + 6] = 0x12; // biXPelsMeter = B12H
	header[32 + 7] = 0x0B;
	header[40 + 2] = 0x12; // biYPelsMeter = B12H
	header[40 + 3] = 0x0B;
	fp = fopen(filename, "wb+");
	if (!fp)
	{
		fprintf(stderr, "Open output bmp file error\n");
		return 1;
	}
	if (sizeof(header) != fwrite(header, 1, sizeof(header), fp))
	{
		fprintf(stderr, "Write output bmp file header error\n");
		fclose(fp);
		return 1;	
	}
	if (flipY == 0 && zeroByteSize == 0)
	{
		if (imagesize != fwrite(data, 1, imagesize, fp))
		{
			fprintf(stderr, "Write output bmp file pixels error\n");
			fclose(fp);
			return 1;
		}
	}
	else
	{
		unsigned int i;
		unsigned char * p = data;
		unsigned char pZero[] = {0x0, 0x0, 0x0, 0x0};

		if (flipY)
		{
			p = data + (height - 1) * width * 3;
		}
		for (i = 0; i < height; i++)
		{
			unsigned int linesize = width * 3;
			if (linesize != fwrite(p, 1, linesize, fp))
			{
				fprintf(stderr, "Write output bmp file pixels error\n");
				fclose(fp);
				return 1;
			}
			if (!flipY)
			{
				p += linesize;
			}
			else
			{
				p -= linesize;
			}
			if (zeroByteSize > 0)
			{
				if (zeroByteSize != fwrite(pZero, 1, zeroByteSize, fp))
				{
					fprintf(stderr, "Write output bmp file pixels error\n");
					fclose(fp);
					return 1;
				}
			}
		}
	}
	fclose(fp);
	return 0;
}
