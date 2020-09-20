// Display.cpp: implementation of the Display class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "Display.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Display::Display()
{
	srand(time(NULL));

	int width = WINDOW_WIDTH;
	int height = WINDOW_HEIGHT;
	MainFrameResize(width, height);
}

Display::~Display()
{

}

void Display::show(Group *group) 
{
	CanvasSetColor(WINDOW_BGCOLOR);
	if (MainFrameGetMsg() != 0) 
	{
		exit(0);
		return;
	}
	CanvasLock();
	//CanvasFillRect(100, 100, width-100, height-100, 0xff0000);
	//CanvasFillRect(0, 0, width-0, height-0, 0xffffff);
	//CanvasDrawLine(100, 100, width-100, height-100, 0xff0000, 0xff);
	//CanvasBitblt(0, 0, 442, 13, 0, 0, 442 / 2, 13, fixedfont_bin, 442, 13, 1);

	for (int k = 0; k < group->get_size(); ++k)
	{
		TileGrid *tile = group->get(k);
		if (tile != NULL)
		{
			bool hidden = tile->get_hidden();
			
			if (hidden)
			{
				//skip
				continue;
			}

			AdafruitImageload *bmp = tile->get_bmp();

			int x = tile->get_x();
			int y = tile->get_y();
			Palette *palette = tile->get_pixel_shader();
			unsigned char *pixels = bmp->get_pixels();
			int width = bmp->get_width();
			int widthByte = bmp->get_width_byte();
			int height = bmp->get_height();

			//printf("width == %d, height == %d\n", width, height);

			//if (tile->get_num_grid_w() > 1)
			//{
			//	printf("tile->get_num_grid_w() > 1\n");
			//}

			int numGridW = tile->get_num_grid_w();
			int numGridH = tile->get_num_grid_h();
			int tileWidth = tile->get_tile_width();
			int tileHeight = tile->get_tile_height();
			int numTileW = bmp->get_width() / tile->get_tile_width();
			int numTileH = bmp->get_height() / tile->get_tile_height();

			for (int jj = 0; jj < numGridH; ++jj)
			{
				for (int ii = 0; ii < numGridW; ++ii)
				{
					int value = tile->get2(ii, jj); //which index of bmp section
					//value = 0;
					int valueH = value / numTileW;
					int valueW = value - valueH * numTileW;
					//valueH = 0;
					//valueW = 0;
					//if (valueH != 0)
					//{
					//	printf("%d\n", valueH);
					//}

					for (int j = 0; j < tileHeight; ++j)
					{
						int jOffset = j + valueH * tileHeight;
						for (int i = 0; i < tileWidth; ++i)
						{
							int iOffset = i + valueW * tileWidth;

							int index_color = ((pixels[jOffset * widthByte + iOffset / 8]) & ((1 << (iOffset % 8)) & 0xff)) ? 1 : 0;
							unsigned int color = palette->get(index_color);
							if (color & 0xff000000)
							{
								color &= 0xffffff;
								CanvasDrawPixel(x + i + ii * tileWidth, y + j + jj * tileHeight, color, 0xff);
							}
							else
							{
								//alpha color, skip
							}
						}
					}
				}
			}

		}
	}

	CanvasUnlock();
	MainFrameRefresh();
	Sleep(FRAME_SLEEP);
}