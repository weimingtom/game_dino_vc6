// DisplayIO.cpp: implementation of the DisplayIO class.
//
//////////////////////////////////////////////////////////////////////

#include "DisplayIO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DisplayIO::DisplayIO()
{

}

DisplayIO::~DisplayIO()
{

}

TileGrid::TileGrid(AdafruitImageload *bmp, Palette *pixel_shader, 
	int width, int height, 
	int tileWidth, int tileHeight, 
	int x, int y, int default_tile) 
{
	this->m_numGridW = (width > 0) ? width : 1; 
	this->m_numGridH = (height > 0) ? height : 1;
	this->m_tileWidth = (tileWidth > 0 && tileWidth <= bmp->get_width()) ? tileWidth : bmp->get_width();
	this->m_tileHeight = (tileHeight > 0 && tileHeight <= bmp->get_height()) ? tileHeight : bmp->get_height();
	this->m_x = x;
	this->m_y = y;
	this->m_tile_id_count = (bmp->get_width() / this->m_tileWidth) * (bmp->get_height() / this->m_tileHeight);
	this->m_default_tile = (default_tile >= 0 && default_tile < this->m_tile_id_count) ? default_tile : 0;
	this->m_tileMap = new int[this->m_numGridW * this->m_numGridH];
	int k = 0;
	for (k = 0; k < this->m_numGridW * this->m_numGridH; ++k)
	{
		this->m_tileMap[k] = this->m_default_tile;
	}
	this->m_hidden = false;
	this->m_pixel_shader = (pixel_shader != NULL) ? pixel_shader : bmp->get_palette();
	this->m_bmp = bmp;
}

TileGrid::~TileGrid() 
{

}

void TileGrid::set(int x, int value) 
{
	this->set2(x, 0, value);
}

void TileGrid::set2(int x, int y, int value) 
{
	this->m_tileMap[y * m_numGridW + x] = value;
}

int TileGrid::get2(int x, int y) 
{
	if (x < 0 || x >= this->m_numGridW)
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}
	if (y < 0 || y >= this->m_numGridH)
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}
	return this->m_tileMap[y * m_numGridW + x];
}

void TileGrid::set_x(int x) 
{
	this->m_x = x;
}

void TileGrid::set_y(int y) 
{
	this->m_y = y;
}

void TileGrid::set_flip_x(bool value) 
{
	//FIXME:TODO
}

void TileGrid::set_hidden(bool value) 
{
	this->m_hidden = value;
}

int TileGrid::get_x() 
{
	return this->m_x;
}

int TileGrid::get_y() 
{
	return this->m_y;
}

void TileGrid::set_pixel_shader(Palette *pixel_shader) 
{
	this->m_pixel_shader = pixel_shader;
}

AdafruitImageload *TileGrid::get_bmp()
{
	return this->m_bmp;
}

Palette *TileGrid::get_pixel_shader()
{
	return this->m_pixel_shader;
}

int TileGrid::get_num_grid_w()
{
	return this->m_numGridW;
}

int TileGrid::get_num_grid_h()
{
	return this->m_numGridH;
}

int TileGrid::get_tile_width()
{
	return this->m_tileWidth;
}

int TileGrid::get_tile_height()
{
	return this->m_tileHeight;
}

bool TileGrid::get_hidden() 
{
	return this->m_hidden;
}

Group::Group(int max_size) 
{
	this->m_max_size = (max_size > 0) ? max_size : 10;
	this->m_tile_grid = new TileGrid *[this->m_max_size];
	this->m_tile_grid_size = 0;
}

Group::~Group() 
{

}

void Group::append(TileGrid *tileGrid) 
{
	if (this->m_tile_grid_size >= this->m_max_size) 
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}
	this->m_tile_grid[this->m_tile_grid_size++] = tileGrid;
}

TileGrid *Group::get(int index)
{
	if (index >= 0 && index < this->m_tile_grid_size)
	{
		return this->m_tile_grid[index];
	}
	else
	{
		return NULL;
	}
}

int Group::get_size()
{
	return this->m_tile_grid_size;
}