#ifndef _READWRITE_H
#define _READWRITE_H
		
#include "diskio.h"		
#include "malloc.h" 
#include "exfuns.h"
FRESULT times_Init(const u8*path);
FRESULT times_Write(const u8*path);
FRESULT times_Read(const u8*path);

#endif
