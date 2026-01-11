#include "Helper.h"
#include "generic_functions.h"
#include "constants.h"


DWORD CreateLibertadoresFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 7) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		//WORD year = *(WORD*)(_this + 0x40);
		*num_rounds = 6;
		*stage_name_id = 1 + NumericGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 2), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 9), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 23), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 7), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 14), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 28), year, Wednesday, Evening);

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 7) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = *(WORD*)(_this + 0x40);
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 7, 16, 8, 16, 0, 0, 2, 7, 0, -1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 8, 4, 0, 0, 0, 2, 7, 0, -1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 4, 2, 0, 0, 0, 2, 7, 0, -1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, 2000000, 800000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) libertadores_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateLibertadoresFixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_libertadores_calendar()
{
	WriteFuncPtr(0x968BF4, 16, (DWORD)&libertadores_fixture_caller);
	// Recopa calendar
	WriteBytes(0x6323ff, 1, 0x0);
	WriteBytes(0x632401, 1, 0x19);
	WriteBytes(0x632415, 3, 0x6a, 0x03, 0x53);
	WriteBytes(0x632419, 1, 0x1);
	WriteBytes(0x63241b, 1, 0x14);
	WriteBytes(0x63245e, 1, 0x7);
}