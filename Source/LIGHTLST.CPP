#include "stdafx.h"
#include "lib3d.h"

CLightList::CLightList (void)
{
}

CLightList::~CLightList (void)
{
	Empty ();
}

void CLightList::Empty (void)
{
	while (!IsEmpty ())
		delete RemoveTail ();		
}