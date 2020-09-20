// Display.h: interface for the Display class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAY_H__98EEDC60_3ED2_46F6_9DC8_8F1C4B9DBB27__INCLUDED_)
#define AFX_DISPLAY_H__98EEDC60_3ED2_46F6_9DC8_8F1C4B9DBB27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DisplayIO.h"

#ifndef FRAME_SLEEP
#define FRAME_SLEEP 20
#endif

//240x240
class Display  
{
public:
	Display();
	virtual ~Display();

	void show(Group *group);
};

#endif // !defined(AFX_DISPLAY_H__98EEDC60_3ED2_46F6_9DC8_8F1C4B9DBB27__INCLUDED_)
