#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

DWORD* eng_league_1_vtable = (DWORD*)0x969DD0;
static DWORD(__thiscall* eng_league_1_subs)(BYTE* _this) = (DWORD(__thiscall*)(BYTE * _this))(0x576780);

DWORD eng_league_1_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 19), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 9), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		Date boxing_day = Date(year, 12, 26);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 27), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 17), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 10), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 17), year, Tuesday, Evening);
		Date easter_day = Date::easter_gregorian(year + 1);
		Date easter_test = Date(year + 1, 3, 21);
		int diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		easter_test = Date(year + 1, 3, 28);
		diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		easter_test = Date(year + 1, 4, 4);
		diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		easter_test = Date(year + 1, 4, 11);
		diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		easter_test = Date(year + 1, 4, 18);
		diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		easter_test = Date(year + 1, 4, 25);
		diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		AddFixtureNoTV(pMem, fixture_id++, diff < 4 ? easter_day : easter_test, year, diff < 4 ? Friday : Saturday, diff < 4 ? Evening : Afternoon);
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, easter_day, year, Monday, Evening);
		}
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 0) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = Playoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 4, 0, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 14), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 24), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) eng_league_1_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_1_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void eng_league_1_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_league_1_vtable;
	data->year = year;
	data->rules = 0x9;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_WHITE_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_GREY_2_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	eng_league_1_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, 723803, get_comp(ENG_CHAMP_9CF()));
	SetupTVMoney(_this, 444000, 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
}

char eng_league_1_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->year++;
	data->current_stage = -1;
	eng_league_1_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, 723803, get_comp(ENG_CHAMP_9CF()));
	SetupTVMoney(_this, 444000, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_league_1_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_1_update
		add esp, 0x4
		ret
	}
}

void setup_eng_league_1() {
	WriteVTablePtr(eng_league_1_vtable, VTableEoSUpdate, (DWORD)&eng_league_1_update_c);
	WriteVTablePtr(eng_league_1_vtable, VTableFixtures, (DWORD)&eng_league_1_fixture_caller);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(eng_league_1_vtable, VTable21, 0x4110b0);
}