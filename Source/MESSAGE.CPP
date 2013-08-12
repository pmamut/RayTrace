#include "stdafx.h"
#include "stdlib.h"
#include "message.h"

void Message (const char* szCaption, const char* szFormat, ...)
{
	char szBuf [512];
	char* pArgs;

	pArgs = (char*) &szFormat + sizeof (szFormat);
	vsprintf (szBuf, szFormat, pArgs);
	::MessageBox (HWND_DESKTOP, szBuf, szCaption, MB_OK | MB_ICONINFORMATION);
//	AfxGetMainWnd ()->MessageBox (szBuf, szCaption, MB_OK | MB_ICONINFORMATION);
}
