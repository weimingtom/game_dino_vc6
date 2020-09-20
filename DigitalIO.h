// DigitalIO.h: interface for the DigitalIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGITALIO_H__4DD6B090_B5B9_435C_BC8F_6C445655F7F8__INCLUDED_)
#define AFX_DIGITALIO_H__4DD6B090_B5B9_435C_BC8F_6C445655F7F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

enum Direction {
	INPUT,
};

enum Pull {
	UP,
};

class DigitalIO  
{
public:
	DigitalIO(int io);
	virtual ~DigitalIO();

	static DigitalIO *DigitalInOut(int io);

	enum Direction direction;
	enum Pull pull;

	int get_value();

private:
	int m_io;
};

#endif // !defined(AFX_DIGITALIO_H__4DD6B090_B5B9_435C_BC8F_6C445655F7F8__INCLUDED_)
