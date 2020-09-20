// DigitalIO.cpp: implementation of the DigitalIO class.
//
//////////////////////////////////////////////////////////////////////

#include "DigitalIO.h"
#include "sdl_api.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DigitalIO::DigitalIO(int io)
: m_io(io)
{

}

DigitalIO::~DigitalIO()
{

}

DigitalIO *DigitalIO::DigitalInOut(int io) 
{ 
	return new DigitalIO(io); 
}

int DigitalIO::get_value() 
{ 
	int key = KeyboardGetKeyboardStatus();
	if (key != 0) {
		//key board event catch
		while (KeyboardGetKeyboardStatus() != 0)
		{
			Sleep(1);
		}
		return 0;
	} else {
		return 1; 
	}
}

