#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\9cf_constants.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "setup_int_friendlies.h"

static void(__thiscall* sub_5CC510)(BYTE* _this) = (void(__thiscall*)(BYTE * _this))(0x5CC510);
void new_friendlies_dates(BYTE* _this) {
	DWORD capacity = 40;
	*((DWORD*)(_this + 0x34F0)) = capacity;
	BYTE* pMem = (BYTE*)cm0102_malloc(capacity * 20);
	int_friendly* list = (int_friendly*)pMem;

	BYTE dates[40][4] = {
		{Thursday, 23, March, 0},
		{Tuesday, 28, March, 0},
		{Thursday, 4, June, 0},
		{Monday, 8, June, 0},
		{Thursday, 23, September, 0},
		{Sunday, 26, September, 0},
		{Wednesday, 29, September, 0},
		{Sunday, 3, October, 0},
		{Thursday, 13, November, 0},
		{Tuesday, 18, November, 0},
		{Thursday, 23, March, 1},
		{Tuesday, 28, March, 1},
		{Wednesday, 9, June, 1},
		{Sunday, 13, June, 1},
		{Thursday, 23, September, 1},
		{Sunday, 26, September, 1},
		{Thursday, 30, September, 1},
		{Monday, 4, October, 1},
		{Thursday, 13, November, 1},
		{Tuesday, 18, November, 1},
		{Thursday, 23, March, 2},
		{Tuesday, 28, March, 2},
		{Friday, 1, June, 2},
		{Monday, 4, June, 2},
		{Thursday, 23, September, 2},
		{Sunday, 26, September, 2},
		{Wednesday, 29, September, 2},
		{Sunday, 3, October, 2},
		{Thursday, 13, November, 2},
		{Tuesday, 18, November, 2},
		{Thursday, 21, March, 3},
		{Tuesday, 26, March, 3},
		{Wednesday, 8, June, 3},
		{Sunday, 12, June, 3},
		{Thursday, 24, September, 3},
		{Sunday, 27, September, 3},
		{Wednesday, 30, September, 3},
		{Sunday, 4, October, 3},
		{Thursday, 13, November, 3},
		{Tuesday, 18, November, 3},
	};

	for (DWORD i = 0; i < capacity; i++) {
		list[i].weekday = dates[i][0];
		list[i].day = dates[i][1];
		list[i].month = dates[i][2];
		list[i].year_offset = dates[i][3];
		list[i].continent = (DWORD)-1;
		list[i].competition = (DWORD)-1;
	}

	*((DWORD*)(_this + 0x34EC)) = (DWORD)pMem;
	sub_5CC510(_this);
	*((WORD*)(_this + 0x34F4)) = 400;
}

void __declspec(naked) new_friendlies_dates_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call new_friendlies_dates
		add esp, 0x4
		ret
	}
}

void new_forbidden_matchups(BYTE* _this) {
	DWORD forbidden[14][2] = {
		{ NATION_UKRAINE_9CF(), NATION_BELARUS_9CF() },
		{ NATION_SPAIN_9CF(), NATION_GIBRALTAR_9CF() },
		{ NATION_ARMENIA_9CF(), NATION_AZERBAIJAN_9CF() },
		{ NATION_UKRAINE_9CF(), NATION_RUSSIA_9CF() },
		{ NATION_KOSOVO_9CF(), NATION_BOSNIA_9CF() },
		{ NATION_KOSOVO_9CF(), NATION_SERBIA_9CF() },
		{ NATION_KOSOVO_9CF(), NATION_RUSSIA_9CF() },
		{ NATION_DR_CONGO_9CF(), NATION_RWANDA_9CF() },
		{ NATION_ISRAEL_9CF(), NATION_PALESTINE_9CF() },
		{ NATION_ISRAEL_9CF(), NATION_IRAN_9CF() },
		{ NATION_NORTH_KOREA_9CF(), NATION_SOUTH_KOREA_9CF() },
		{ NATION_NORTH_KOREA_9CF(), NATION_JAPAN_9CF() },
		{ NATION_NORTHERN_IRELAND_9CF(), NATION_IRELAND_9CF() },
		{ NATION_IRAN_9CF(), NATION_IRAQ_9CF() },
	};

	BYTE num = 14;
	*((BYTE*)(_this + 0x3506)) = num;
	DWORD* pMem = (DWORD*)cm0102_malloc(num * 8);
	*((DWORD*)(_this + 0x3502)) = (DWORD)pMem;

	for (BYTE i = 0; i < num; i++) {
		pMem[i * 2] = forbidden[i][0];
		pMem[i * 2 + 1] = forbidden[i][1];
	}
}

void __declspec(naked) new_forbidden_matchups_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call new_forbidden_matchups
		add esp, 0x4
		ret
	}
}

void setup_int_friendlies() {
	WriteJMP(0x5CA4F0, (DWORD)&new_friendlies_dates_c);
	WriteJMP(0x5CC2D0, (DWORD)&new_forbidden_matchups_c);
	WriteBytes(0x5CBEBB, 1, 2); // friendlies must be over 2 days apart instead of over 4 days
	WriteBytes(0x5CBEDB, 1, 2); // friendlies must be over 2 days apart instead of over 4 days
	WriteBytes(0x5CC08D, 1, 0xEB); // remove check with Africa?
	WriteBytes(0x5CC142, 1, 0xEB); // remove check with Africa?
	WriteDWORD(0x5CC0D6, 800); // increase chances of friendly with teams from different continent
	WriteDWORD(0x5CC18E, 200); // reduce chances of friendly with teams from same continent
}