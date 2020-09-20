// DisplayIO.h: interface for the DisplayIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYIO_H__27CE2341_7052_41B3_839A_FE6BCADABB97__INCLUDED_)
#define AFX_DISPLAYIO_H__27CE2341_7052_41B3_839A_FE6BCADABB97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sdl_api.h"
#include "AdafruitImageload.h"

class DisplayIO  
{
public:
	DisplayIO();
	virtual ~DisplayIO();

	enum {Bitmap = 1001, Palette = 1002, };
};

class TileGrid
{
public:
	TileGrid(AdafruitImageload *bmp, Palette *pixel_shader, 
		int width = 0, int height = 0, 
		int tileWidth = 0, int tileHeight = 0, 
		int x = 0, int y = 0, int default_tile=-1);
	virtual ~TileGrid();
	void set(int x, int value);
	void set2(int x, int y, int value);
	int get2(int x, int y); 
	void set_x(int x);
	void set_y(int y);
	void set_flip_x(bool value);
	void set_hidden(bool value);
	int get_x();
	int get_y();
	void set_pixel_shader(Palette *pixel_shader);
	Palette *get_pixel_shader();
	AdafruitImageload *get_bmp();
	int get_num_grid_w();
	int get_num_grid_h();
	int get_tile_width();
	int get_tile_height();
	bool get_hidden(); 

private:
	int m_numGridW;
	int m_numGridH;
	int m_tileWidth;
	int m_tileHeight;
	int m_x;
	int m_y;
	int m_default_tile;
	bool m_hidden;

	int *m_tileMap;
	int m_tile_id_count;
	Palette *m_pixel_shader;
	AdafruitImageload *m_bmp;
};

class Group
{
public:
	Group(int max_size);
	virtual ~Group();

	void append(TileGrid *tileGrid);
	
	TileGrid *get(int index);
	int get_size();

private:
	TileGrid **m_tile_grid;
	int m_tile_grid_size;
	int m_max_size;
};

#endif // !defined(AFX_DISPLAYIO_H__27CE2341_7052_41B3_839A_FE6BCADABB97__INCLUDED_)
