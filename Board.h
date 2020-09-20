// Board.h: interface for the Board class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOARD_H__00D5663F_A1D8_4E7D_A19D_64AB13B67EA3__INCLUDED_)
#define AFX_BOARD_H__00D5663F_A1D8_4E7D_A19D_64AB13B67EA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Display.h"

class Board  
{
public:
	Board();
	virtual ~Board();

	enum { 
		USR_BTN = 0,
	};

	static Display *DISPLAY;
};

#endif // !defined(AFX_BOARD_H__00D5663F_A1D8_4E7D_A19D_64AB13B67EA3__INCLUDED_)
