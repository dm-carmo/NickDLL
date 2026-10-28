#pragma once

#pragma pack(push, 1)
typedef struct INT_FRIENDLY
{
	BYTE weekday;
	BYTE day;
	BYTE month;
	BYTE date[8];
	BYTE year_offset;
	DWORD continent;
	DWORD competition;
} int_friendly;
#pragma pack(pop)

void setup_int_friendlies();