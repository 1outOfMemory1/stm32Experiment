#include "sys.h"



void DelayMs(u32 nMs)
{
	u32 i;
	
	for(; nMs !=0; nMs--)
	{
		i = 10301;
		while(i--);
	}
}

