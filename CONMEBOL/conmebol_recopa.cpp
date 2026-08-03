#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* conmebol_recopa_vtable = (DWORD*)0x96BAD8;


DWORD conmebol_recopa_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 20), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, None, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 2, 0, 0, 2, 7, 0, prizeMoneyFile.GetInt("conmebol_recopa_final_win"), prizeMoneyFile.GetInt("conmebol_recopa_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) conmebol_recopa_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_recopa_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_conmebol_recopa()
{
	WriteVTablePtr(conmebol_recopa_vtable, VTableFixtures, (DWORD)&conmebol_recopa_fixture_caller);
}
