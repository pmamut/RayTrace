#include "stdafx.h"
#include "lib3d.h"

CObjectList::CObjectList (void)
{
}

CObjectList::~CObjectList (void)
{
	Empty ();
}

void CObjectList::Empty (void)
{
	while (!IsEmpty ())
		delete RemoveTail ();		
}