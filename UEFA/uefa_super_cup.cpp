#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* uefa_super_cup_vtable = (DWORD*)0x969F80;


DWORD uefa_super_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, None, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0, 0, 2250000, 1800000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uefa_super_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_super_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_uefa_super_cup()
{
	WriteVTablePtr(uefa_super_cup_vtable, VTableFixtures, (DWORD)&uefa_super_cup_fixture_caller);
}
