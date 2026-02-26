#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* uefa_champions_league_vtable = (DWORD*)0x96A1D0;

static __int16(__thiscall* sub_48E1C0)(BYTE* _this, DWORD* a2, int a3) =
(__int16(__thiscall*)(BYTE * _this, DWORD * a2, int a3))(0x48E1C0);
static int(__thiscall* sub_48E3E0)(BYTE* _this, BYTE* a2, int a3, int a4, char a5, __int16 a6, BYTE* a7, char a8) =
(int(__thiscall*)(BYTE * _this, BYTE * a2, int a3, int a4, char a5, __int16 a6, BYTE * a7, char a8))(0x48E3E0);
static int(__thiscall* sub_5A0590)(BYTE* _this, BYTE* a2) =
(int(__thiscall*)(BYTE * _this, BYTE * a2))(0x5A0590);
static int(__thiscall* sub_51A150)(BYTE* _this, BYTE* a2, int a3) =
(int(__thiscall*)(BYTE * _this, BYTE * a2, int a3))(0x51A150);
static int(__thiscall* sub_5999A0)(BYTE* _this, int a2) =
(int(__thiscall*)(BYTE * _this, int a2))(0x5999A0);
static __int16(__thiscall* sub_9035A0)(BYTE* _this, int a2) =
(__int16(__thiscall*)(BYTE * _this, int a2))(0x9035A0);
static int(__thiscall* sub_9058B0)(BYTE* _this, BYTE* a2, char a3) =
(int(__thiscall*)(BYTE * _this, BYTE * a2, char a3))(0x9058B0);

int uefa_champions_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[8];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) uefa_champions_league_set_champion_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD uefa_champions_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 12), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstQualifyingPhase, 4, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 18, 9, 18, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondQualifyingPhase, 4, FixedTeamOrderInCup2 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 28, 14, 19, 18, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 9), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdQualifyingPhase, 4, FixedTeamOrderInCup2 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 32, 16, 18, 37, 0, 2, 7);

		return (DWORD)pMem;
	}
	else if (stage_idx < 8) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 4;
		*num_rounds = 6;
		*stage_name_id = Phase1GroupAtoH + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 4)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 7), year, Tuesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 26), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 24), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Wednesday, Evening);
		}

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 12) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 4;
		*num_rounds = 6;
		*stage_name_id = Phase2GroupAtoD + stage_idx - 8;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 10)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 10), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 13), year, Tuesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 5), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 13), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 6), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Wednesday, Evening);
		}

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 12) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 8, 4, 8, 0, 0, 2, 14, 1600000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 20), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 4, 2, 0, 0, 0, 2, 7, 2000000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 26), year, Saturday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, 4000000, 3200000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uefa_champions_league_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_champions_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void uefa_champions_league_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 71;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	DWORD teams_r3 = 0;
	DWORD teams_r4 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == UEFA_CHAMPIONS_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 16) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 18) {
				teams[teams_r2 + 16].club = club;
				teams[teams_r2 + 16].f5 = 8;
				teams[teams_r2 + 16].f6 = 0;
				teams_r2++;
			}
			else if (seed == 3 && teams_r3 < 19) {
				teams[teams_r3 + 34].club = club;
				teams[teams_r3 + 34].f5 = 13;
				teams[teams_r3 + 34].f6 = 0;
				teams_r3++;
			}
			else if (seed == 4 && teams_r4 < 18) {
				teams[teams_r4 + 53].club = club;
				teams[teams_r4 + 53].f5 = 0;
				teams[teams_r4 + 53].f6 = 0;
				teams_r4++;
			}
		}
	}

	//dprintf("r1: %d, r2: %d, r3: %d, r4: %d\n", teams_r1, teams_r2, teams_r3, teams_r4);
}

void uefa_champions_league_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 55;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	DWORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (DWORD i = 0; i < total_teams; i++) {
		teams[i].club = qualifiers[total_count - i - 1].club;
		BYTE seed = qualifiers[total_count - i - 1].f5;
		if (seed == 8) {
			teams[i].f5 = 2;
		}
		else if (seed == 13) {
			teams[i].f5 = 1;
		}
		else {
			teams[i].f5 = 0;
		}
		teams[i].f6 = 0;
	}
}

void uefa_champions_league_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->special_teams_seedings;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->special_nteams_seedings; i++)
		{
			clubs.push_back(all_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 12; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 16; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 24; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (int i = 32; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 48; i < 62; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (int i = 62; i < 71; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 63);
		}
	}
}

void __declspec(naked) uefa_champions_league_reputation_setup_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_reputation_setup
		add esp, 0x4
		ret
	}
}

void uefa_champions_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = (char)pow(2, current + 4) + 1;
		ret_min = (char)pow(2, min + 4) + 1;
		ret_max = (char)pow(2, max + 4) + 1;
	}
	else if (stage < 8) {
		ret_current = 1 + 8 * (current - 1);
		ret_min = 1 + 8 * (min - 1);
		ret_max = 1 + 8 * (max - 1);
	}
	else if (stage < 12) {
		ret_current = 1 + 4 * (current - 1);
		ret_min = 1 + 4 * (min - 1);
		ret_max = 1 + 4 * (max - 1);
	}
	else if (stage == 12) {
		if (current < 4) ret_current = current;
		else ret_current = (char)pow(2, current - 2) + 1;
		if (min < 4) ret_min = min;
		else ret_min = (char)pow(2, min - 2) + 1;
		if (max < 4) ret_max = max;
		else ret_max = (char)pow(2, max - 2) + 1;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) uefa_champions_league_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_champions_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

// prize money for group stages
int ucl_583B10(BYTE* _this, BYTE* a2, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	char al, cl;
	cm3_clubs* club_check = 0;
	al = *(char*)(a2 + 0x47);
	if (al == -1) {
		al = *(char*)(a2 + 0x43);
		cl = *(char*)(a2 + 0x44);
	}
	else cl = *(char*)(a2 + 0x48);
	if (al == cl) {
		cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club1->ClubNation), 1);
		cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club2->ClubNation), 1);
	}
	else if (al > cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club_check->ClubNation), 2);
	}
	else {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club_check->ClubNation), 2);
	}
	al = *(char*)(a2 + 0x42);
	// group stage indexes
	if (al > -1 && al < 12) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			sub_5999A0((BYTE*)ret, 200000);
			sub_48E3E0(_this, (BYTE*)club_check, 200000, 0, -1, 0, a2, -2);
		}
		else {
			cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
			sub_5999A0((BYTE*)ret, 100000);
			cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
			sub_5999A0((BYTE*)ret, 100000);
			sub_48E3E0(_this, (BYTE*)club1, 100000, 0, -1, 0, a2, -2);
			sub_48E3E0(_this, (BYTE*)club2, 100000, 0, -1, 0, a2, -2);
		}
	}
	return sub_51A150(_this, a2, a3);
}

void __declspec(naked) ucl_583B10_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_583B10
		add esp, 0xc
		ret 8
	}
}

int ucl_586660(BYTE* _this, DWORD* a2, char a3) {
	comp_stats* data = (comp_stats*)_this;
	if (a3 == 1) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID && t.f5 != 7) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}
	if (a3 == 2) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}
	if (a3 == 3 && data->current_stage == 11) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}

	return sub_48E1C0(_this, a2, 0);
}

void __declspec(naked) ucl_586660_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_586660
		add esp, 0xc
		ret 8
	}
}

char uefa_champions_league_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
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
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_champions_league_all_teams(_this); //584fa0
	uefa_champions_league_qualifier_teams(_this); //584990
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) uefa_champions_league_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_update
		add esp, 0x4
		ret
	}
}

void uefa_champions_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = uefa_champions_league_vtable;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 13; // to review
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATITONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x1;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_champions_league_all_teams(_this); //584fa0
	uefa_champions_league_qualifier_teams(_this); //584990
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	uefa_champions_league_reputation_setup(_this); //586900
}

void uefa_champions_league_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { 4, 1, 2, 0 };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < 16; i++) {
		clubs.push_back(teams[i].club);
	}

	for (WORD j = 0; j < comp_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[j];
		if (t.f6 == 1) {
			clubs.push_back(t.club);
		}
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 16, rng);
	shuffle(clubs.begin() + 16, clubs.begin() + 24, rng);
	shuffle(clubs.begin() + 24, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 0; i < 8; i++) {
		DWORD v1 = *(DWORD*)_this;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i, &num_rounds, &stage_name_id, 0);
		comp_stats* data = (comp_stats*)_this;
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 8 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			sub_5999A0((BYTE*)ret, 1800000);
			sub_48E3E0(_this, (BYTE*)club, 1800000, 0, -1, Phase1, 0, -2);
		}

		WORD year = data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i, stage_name_id, 0xf, 2, 0, 8, -1, 0, 2);
		DWORD* stages_arr = data->stages;
		*((DWORD*)(&stages_arr[i])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		data->current_stage = i;
	}

	BYTE* uel_bytes = get_loaded_league(UEFA_EUROPA_LEAGUE_9CF());
	if (uel_bytes) {
		comp_stats* uel_data = (comp_stats*)uel_bytes;
		DWORD uel_offset = uel_data->n_teams - 24; // 16 teams joining now from UCL + 8 joining from UCL later

		teams_seeded* uel_teams = (teams_seeded*)uel_data->teams_list;
		for (WORD j = 0; j < comp_data->n_teams; j++) {
			teams_seeded t = ((teams_seeded*)comp_data->teams_list)[j];
			if (t.f6 == 2) {
				uel_teams[uel_offset].club = t.club;
				uel_teams[uel_offset].f5 = 0;
				uel_teams[uel_offset].f6 = 0;
				uel_offset++;

				WORD n_seeds = uel_data->special_nteams_seedings;
				teams_seeded* uel_teams_seeds = (teams_seeded*)uel_data->special_teams_seedings;
				uel_teams_seeds[n_seeds].club = t.club;
				uel_teams_seeds[n_seeds].f5 = 5;
				uel_data->special_nteams_seedings++;

				t.club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
			}
		}

		DWORD v2 = *(DWORD*)uel_bytes;
		(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(uel_bytes);
	}
}

void uefa_champions_league_group_stage_two_setup(BYTE* _this) {
	char stage_num = 8;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { 4, 1, 2, 0 };

	vector<cm3_clubs*> clubs;

	for (char al = 0; al < 8; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 8; i < 12; i++) {
		DWORD v1 = *(DWORD*)_this;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i, &num_rounds, &stage_name_id, 0);
		comp_stats* data = (comp_stats*)_this;
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[(i - 8) + 4 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			sub_5999A0((BYTE*)ret, 1200000);
			sub_48E3E0(_this, (BYTE*)club, 1200000, 0, -1, Phase2, 0, -2);
		}

		WORD year = data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i, stage_name_id, 0xf, 2, 0, 8, -1, 0, 2);
		DWORD* stages_arr = data->stages;
		*((DWORD*)(&stages_arr[i])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		data->current_stage = i;
	}

	BYTE* uel_bytes = get_loaded_league(UEFA_EUROPA_LEAGUE_9CF());
	if (uel_bytes) {
		comp_stats* uel_data = (comp_stats*)uel_bytes;
		DWORD uel_offset = uel_data->n_teams - 8;

		teams_seeded* uel_teams = (teams_seeded*)uel_data->teams_list;
		for (char al = 0; al < 8; al++) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
			team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
			uel_teams[uel_offset].club = t.club;
			uel_teams[uel_offset].f5 = 0;
			uel_teams[uel_offset].f6 = 0;
			uel_offset++;

			WORD n_seeds = uel_data->special_nteams_seedings;
			teams_seeded* uel_teams_seeds = (teams_seeded*)uel_data->special_teams_seedings;
			uel_teams_seeds[n_seeds].club = t.club;
			uel_teams_seeds[n_seeds].f5 = 5;
			uel_data->special_nteams_seedings++;

			t.club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();

			t = ((team_league_stats*)(curr_stage->team_league_table))[3];
			t.club->ClubEuroFlag = -1;
		}

		DWORD v2 = *(DWORD*)uel_bytes;
		(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(uel_bytes);
	}
}

void uefa_champions_league_final_stage_setup(BYTE* _this) {
	char stage_num = 12;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	for (char al = 8; al < 12; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		*((DWORD*)(&pTeams[(al - 8) * 2])) = (DWORD)table_teams[0].club;
		*((DWORD*)(&pTeams[(al - 8) * 2 + 1])) = (DWORD)table_teams[1].club;
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	for (char al = 8; al < 12; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		t.club->ClubEuroFlag = -1;
	}
}

void uefa_champions_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			uefa_champions_league_group_stage_setup(_this);
		}
		else if (current == 8) {
			uefa_champions_league_group_stage_two_setup(_this);
		}
		else if (current == 12) {
			uefa_champions_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) uefa_champions_league_stages_create_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_stages_create
		add esp, 0x4
		ret
	}
}

int uefa_champions_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Phase1, 0x1E);
			//*a5 = 1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 8) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Phase2, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Phase1, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 12) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Phase2, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 12) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = stage_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			//*a5 = 1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) uefa_champions_league_set_table_fate()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_champions_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

char ucl_team_selection(BYTE* _this, BYTE* club_list, int club_count) {
	// Last winner of Champions League

	// Last winner of Europa League

	// Remaining teams
	// Groups, 3rd QR, 2nd QR, 1st QR
	BYTE quals_1[4] = { 2,2,0,0 }; // 1 to 3
	BYTE quals_2[4] = { 2,1,0,0 }; // 4 to 6
	BYTE quals_3[4] = { 1,1,0,0 }; // 7 to 9
	BYTE quals_4[4] = { 1,0,1,0 }; // 10
	BYTE quals_5[4] = { 0,1,1,0 }; // 11 to 15
	BYTE quals_6[4] = { 0,1,0,0 }; // 16
	BYTE quals_7[4] = { 0,0,1,0 }; // 17 to 29
	BYTE quals_8[4] = { 0,0,0,1 }; // 30 to 48
	BYTE quals_9[4] = { 0,0,0,0 }; // rest
	char i;
	for (i = 0; i < 55; i++) {
		uefa_seedings* u = &(*uefa_seeding_list)[i];
		cm3_nations* euro_country = get_country(u->id);
		vector<cm3_clubs*> clubs;
		if (euro_country->NationLeagueSelected) {
			// playable
			clubs = find_clubs_of_country_for_euro_playable(u->id);
			sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
		}
		else {
			// not playable
			clubs = find_clubs_of_country_for_euro(u->id);
			sort(clubs.begin(), clubs.end(), compareClubRep);
		}
		BYTE* quals;
		if (i < 3) quals = quals_1;
		else if (i < 6) quals = quals_2;
		else if (i < 9) quals = quals_3;
		else if (i < 10) quals = quals_4;
		else if (i < 15) quals = quals_5;
		else if (i < 16) quals = quals_6;
		else if (i < 29) quals = quals_7;
		else if (i < 48) quals = quals_8;
		else quals = quals_9;

		BYTE count = 0;
		BYTE curr_seeding = 0;
		for (int x = 0; x < 4; x++) {
			count += quals[x];
			curr_seeding = x + 1;
			if (quals[x] > 0) break;
		}
		for (BYTE j = 0; j < u->ucl_spots; j++) {
			cm3_clubs* euro_club = clubs[0];
			euro_club->ClubEuroFlag = UEFA_CHAMPIONS_LEAGUE_9CF();
			if (j >= count) {
				for (int x = curr_seeding; x < 4; x++) {
					count += quals[x];
					curr_seeding = x + 1;
					if (quals[x] > 0) break;
				}
				if (curr_seeding > 3) break;
			}
			euro_club->ClubEuroSeeding = curr_seeding;
			u->num_teams_in_comps++;
			clubs.erase(clubs.begin());
		}
		u->num_teams_in_comps++;
	}
	return i;
}

void __declspec(naked) ucl_team_selection_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_team_selection
		add esp, 0xc
		ret 8
	}
}

void setup_uefa_champions_league() {
	WriteVTablePtr(uefa_champions_league_vtable, VTable2, (DWORD)&ucl_583B10_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableEoSUpdate, (DWORD)&uefa_champions_league_update_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTablePlayoffQual, (DWORD)&uefa_champions_league_stages_create_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableSetChampion, (DWORD)&uefa_champions_league_set_champion_c);
	//WriteVTablePtr(uefa_champions_league_vtable, VTable15, 0x??); // find the default function and add it later
	WriteVTablePtr(uefa_champions_league_vtable, VTableFixtures, (DWORD)&uefa_champions_league_fixture_caller);
	WriteVTablePtr(uefa_champions_league_vtable, VTableTableFates, (DWORD)&uefa_champions_league_set_table_fate);
	//WriteVTablePtr(uefa_champions_league_vtable, VTableStageNews, 0x48C6D0); // review much later
	WriteVTablePtr(uefa_champions_league_vtable, VTable23, (DWORD)&ucl_586660_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableReputationSetup, (DWORD)&uefa_champions_league_reputation_setup_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableReputationCalc, (DWORD)&uefa_champions_league_reputation_calc_c);

	PatchFunction(0x904210, (DWORD)&ucl_team_selection_c);
}